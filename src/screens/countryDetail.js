import React, { useEffect, useState } from 'react'
import CardMedia from '@material-ui/core/CardMedia';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import { Grid, Divider } from "@material-ui/core";
import Colapsable from "../customcomponents/colapsable";
import Fab from '@material-ui/core/Fab';
import { Mail } from '@material-ui/icons';
import MailOutlineIcon from '@material-ui/icons/MailOutline';
import { Subscribe, Unsubscribe } from '../services/subscriptionService'
import { AlertContext } from "../contexts/AlertContext"
import { Tooltip } from '@material-ui/core';
import { AuthContext } from "../contexts/AuthContext";
import { useParams } from 'react-router-dom';
import { getSpecificCountryService } from "../services/searchService";
import { useHistory } from 'react-router-dom';



const toTitleCase = (str) => {
    return str.replace(
        /\w\S*/g,
        function (txt) {
            return txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase();
        }
    );
}
// const split = (str, sstr) => {
//     let p = str.split(sstr)
//     return p[0]
//   }
  

function camelCaseToTitleCase(camelCase) {
    if (camelCase === null || camelCase === "") {
        return camelCase;
    }

    camelCase = camelCase.trim();
    var newText = "";
    for (var i = 0; i < camelCase.length; i++) {
        if (/[A-Z]/.test(camelCase[i])
            && i !== 0
            && /[a-z]/.test(camelCase[i - 1])) {
            newText += " ";
        }
        if (i === 0 && /[a-z]/.test(camelCase[i])) {
            newText += camelCase[i].toUpperCase();
        } else {
            newText += camelCase[i];
        }
    }

    return newText;
}


const useStyles = makeStyles({
    media: {
        height: 140,
        width: 250,
        borderRadius: 15,
        marginRight: "20px"
    },
});
function CountryDetail() {
    const params = useParams();
    let [country, setCountry] = useState({});
    let [found, setfound] = useState(false);
    let [foundmsg, setfoundmsg] = useState("Searching...");
    useEffect(async () => {
        if (params.countryid) {
            let res = await getSpecificCountryService(params.countryid)
            if (res.data) {
                setCountry(res.data)
                setfound(true)
            }
            else if (res === 404) {
                setfoundmsg("Location Not Found")
            }
        }
    }, [])
    const classes = useStyles();
    const [auth, setAuth] = React.useContext(AuthContext)
    const history = useHistory();

    let subsStatus = auth.sessionID !== "" ? auth.subscriptions.includes(country.countryCode) : false
    let authStatus = auth.sessionID !== "" ? false : true
    const value = React.useContext(AlertContext)

    let details = found ? Object.keys(country.detailsStatus).filter((k) => country.detailsStatus[k] !== "")
        .reduce((a, k) => ({ ...a, [k]: country.detailsStatus[k] }), {}) : {}
    details = Object.keys(details)

    let imgSrc = `${process.env.PUBLIC_URL}/SVG/${country.countryCode}.svg`
    let imgSrc1 = `${process.env.PUBLIC_URL}/SVG/search.gif`


    const handelSubscription = async (subsStatus) => {

        let countryId = country.countryCode
        try {
            value.startLoader()

            let response = subsStatus ? await Subscribe({
                "sessionID": auth.sessionID,
                "location": countryId
            }) : await Unsubscribe({
                "sessionID": auth.sessionID,
                "location": countryId
            })
            value.stopLoader()

            if (!response.error) {
                let p = auth.subscriptions
                let subsArr
                if (subsStatus) {
                    p.push(country.countryCode)

                    subsArr = {
                        subscriptions: p
                    }
                } else {
                    const index = p.indexOf(country.countryCode);
                    if (index > -1) {
                        p.splice(index, 1);
                    }
                    subsArr = {
                        subscriptions: p
                    }
                }


                let v = { ...auth, ...subsArr }
                localStorage.setItem('auth', JSON.stringify(v))
                setAuth(v)
                let msg = subsStatus ? "Sucessfully subscribed" : "Sucessfully Unsubscribed"
                value.showAlert("success", msg)

            }
            else {
                if (response.error.response.data === 'Invalid session') {
                    value.showAlert("error", "Invalid session")
                    localStorage.removeItem('auth')
                    history.push("/signin")
                    setAuth({
                        name: "",
                        subscriptions: [],
                        email: "",
                        sessionID: ""
                    })

                }
                value.showAlert("error", "Something went wrong")
            }

        } catch (error) {
            value.showAlert("error", "Something went wrong")

        }



    }

    let zoneCloro = found ? country.stats.zoneStatus ? country.stats.zoneStatus : 'GREEN' : 'GREEN'
    let stats = found ? Object.keys(country.stats).filter((k) => country.stats[k] !== "" || country.stats[k] < 0)
        .reduce((a, k) => ({ ...a, [k]: country.stats[k] }), {}) : {}
    stats = Object.keys(stats)

   

    //   '#fcc428'

    return (
        <div style={{ display: 'flex', width: "100%", height: "82%", flexDirection: "column", alignItems: "center" }} >
            {found ? <div style={{ display: 'flex', width: "100%", height: "100%", flexDirection: "column", alignItems: "center" }} >
                <div style={{ backgroundColor: zoneCloro, width: "100%", alignItems: "center", display: 'flex', justifyContent: 'center', marginBottom: '10px' }}>
                    <Typography variant="button" gutterBottom style={{ color: 'white' }}>
                        Zone Status: {zoneCloro}
                    </Typography>
                </div>
                {/* <div style={{ display: 'flex', width: "95%",height: "100%", flexDirection: "column", alignItems: "center" }} > */}
                <div style={{ display: 'flex', width: "98%", justifyContent: 'center', alignItems: "center", marginTop: "0px", marginBottom: "10px", flexDirection: "row" }}>
                    <div style={{ display: 'flex', width: "100%", justifyContent: 'flex-start', alignItems: "center", marginTop: "0px", flexDirection: "row" }}>
                        <CardMedia
                            className={classes.media}
                            image={imgSrc}
                            title="Contemplative Reptile"
                        />
                        <br />
                        <div style={{flexDirection:"column"}}>
                        <Typography gutterBottom variant="h4" component="h2">
                            {country.countryName}
                        </Typography>
                        <Typography gutterBottom variant="body1">
                            Update at {country.updatedDate}
                        </Typography>
                        </div>
                    </div>
                    <Tooltip title={!authStatus ? subsStatus ? "Remove from email notification list" : "Add to email notification list" : "Sign Up or Login to subscribe Email Notification"} arrow>
                        <div>
                            <Fab aria-label="subscribe" disabled={authStatus} color="primary" onClick={() => handelSubscription(!subsStatus)}>
                                {subsStatus ? <Mail /> : <MailOutlineIcon />}
                            </Fab>
                        </div>
                    </Tooltip>
                    {/* <br /> */}

                </div>
                <Divider />
                <div style={{ display: 'flex', width: "98%", flexDirection: "row", height: "15%", alignItems: "center", marginBottom: "10px" }}>
                    <Grid container justify='space-around' spacing={0} wrap='nowrap' >
                        {stats.map((item1, index) => {
                            if (country.stats[item1] !== null && item1 !== 'zoneStatus')
                                return <Grid item key={index} >

                                    <div style={{ display: 'flex', padding: "15px", flexDirection: "column", backgroundColor: "white", justifyContent: "center", alignItems: "center", boxShadow: "rgba(50, 50, 93, 0.25) 0px 50px 100px -20px, rgba(0, 0, 0, 0.3) 0px 30px 60px -30px, rgba(10, 37, 64, 0.35) 0px -2px 6px 0px inset", borderRadius: "10px" }}>
                                        <Typography variant="button" gutterBottom>
                                            {toTitleCase(item1)}
                                        </Typography>
                                        {/* {toTitleCase(country.stats[item1])} */}
                                        {country.stats[item1]}
                                    </div>
                                </Grid>

                            return
                        })}
                    </Grid>
                </div>
                <div style={{ overflowX: "hidden", width: '100%', marginBottom: "5px", paddingTop: "5px", display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                    {details.map((item, index) => {

                        let obj = {
                            titel: camelCaseToTitleCase(item), highlite: "", summary: country.detailsStatus[item]

                        }
                        return <Colapsable key={index} detail={obj} />
                    })}

                    {/* </div> */}
                </div>
            </div> :
                <div style={{ display: 'flex', width: "100%", height: "82%", justifyContent: "center", flexDirection: 'column', alignItems: "center" }} >
                    <CardMedia
                        className={classes.media}
                        image={imgSrc1}
                        title="Contemplative Reptile"
                    />

                    <Typography gutterBottom variant="h6" component="h6" style={{ color: foundmsg !== "Searching..." ? "red" : "#c4c4c4" }}>
                        {foundmsg}
                    </Typography>
                </div>
            }
        </div>
    )
}




export default CountryDetail

