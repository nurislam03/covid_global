import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Card from '@material-ui/core/Card';
import { Tooltip } from '@material-ui/core';
import CardActionArea from '@material-ui/core/CardActionArea';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import CardMedia from '@material-ui/core/CardMedia';
import Button from '@material-ui/core/Button';
import Typography from '@material-ui/core/Typography';
import PropTypes from 'prop-types';
import { AuthContext } from "../contexts/AuthContext"
import IconButton from '@material-ui/core/IconButton';
import MailOutlineIcon from '@material-ui/icons/MailOutline';              
import {Mail} from '@material-ui/icons';              
import Divider from '@material-ui/core/Divider'
import { Link } from 'react-router-dom';
import { Subscribe, Unsubscribe } from '../services/subscriptionService'
import { AlertContext } from "../contexts/AlertContext"
import { useHistory } from 'react-router-dom';




const useStyles = makeStyles({
  root: {
    width: 300

  },
  media: {
    height: 140
  },
});
const toTitleCase = (str) => {
  let str1 = split(str, "Status")
  return str1.replace(
    /\w\S*/g,
    function (txt) {
      return txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase();
    }
  );
}


const split = (str, sstr) => {
  let p = str.split(sstr)
  return p[0]
}

export default function SimpleCard({ country }) {
  const history = useHistory();

  const classes = useStyles();
  let imgSrc = `${process.env.PUBLIC_URL}/SVG/${country.countryCode}.svg`
  const [auth, setAuth] = React.useContext(AuthContext)
  let subsStatus = auth.sessionID !== "" ? auth.subscriptions.includes(country.countryCode) : false
  let authStatus = auth.sessionID !== "" ? false : true

  let stat = Object.keys(country.status).filter((k) => country.status[k] !== "")
    .reduce((a, k) => ({ ...a, [k]: country.status[k] }), {});
    stat = Object.keys(stat)
  const value = React.useContext(AlertContext)


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
  let zoneCloro = country.stats.zoneStatus?country.stats.zoneStatus:'GREEN'


  return (
    <Card className={classes.root}>
      <CardActionArea>
        <CardMedia
          className={classes.media}
          image={imgSrc}
          title="Contemplative Reptile"
        />
        <Divider />
        <CardContent>
          <Typography gutterBottom variant="h6" component="h2">
            {country.countryName}
          </Typography>

          {/* <li>Tourism : {country.countryCode}</li>
         <li>Quarantine: {country.countryCode} </li>
         <li>Lockdown : {country.countryCode}</li> */}
          {country.status && <div style={{ display: 'flex', flex: 1, flexDirection: "column" }}>
            <div style={{ display: 'flex', flex: 1, flexDirection: "row" }}  >

              <div style={{ width: 80, height: 18, marginRight: "2px" }}>
                <Typography variant="body2" >
                  Zone Status
                </Typography>
              </div>
              <div style={{ width: 10, height: 18, marginRight: "2px" }}>
              <Typography variant="body2" >
                  :
                </Typography>
              </div>
              <div style={{ width: 70, height: 18 }}>
                <Typography variant="body2" style={{ color:zoneCloro}}>
                {zoneCloro}
                </Typography>

              </div>

            </div>
            {stat.map((item, index) => (
              <div style={{ display: 'flex', flex: 1, flexDirection: "row" }} key={index} >

                <div style={{ width: 80, height: 18, marginRight: "2px" }}>
                  <Typography variant="body2" >
                    {toTitleCase(item)}
                  </Typography>
                </div>
                <div style={{ width: 10, height: 18, marginRight: "2px" }}>
                <Typography variant="body2" >
                  :
                </Typography>
                </div>
                <div style={{ width: 70, height: 18 }}>
                  <Typography variant="body2" >
                    {toTitleCase(country.status[item])}
                  </Typography>
                </div>

              </div>
            ))}</div>}
          <div style={{ height: "10px", display: 'flex', justifyContent: "center" }}></div>
          <div style={{ display: 'flex', flex: 1, flexDirection: "row", justifyContent: "space-around", marginBottom: "10px" }}>
            <div style={{ display: 'flex', height: 70, width: "32%", flexDirection: "column", justifyContent: "center", alignItems: "center", borderRadius: "10px", boxShadow: "rgba(0, 0, 0, 0.16) 0px 1px 4px" }}>
              <Typography variant="button" gutterBottom>
                {country.stats.totalCase}
              </Typography>
              Total Cases
            </div>
            <div style={{ display: 'flex', height: 70, width: "32%", flexDirection: "column", justifyContent: "center", alignItems: "center", borderRadius: "10px", boxShadow: "rgba(0, 0, 0, 0.16) 0px 1px 4px" }}>
              <Typography variant="button" gutterBottom>
                {country.stats.newCase}

              </Typography>

              New Cases

            </div>
            <div style={{ display: 'flex', height: 70, width: "32%", flexDirection: "column", justifyContent: "center", alignItems: "center", borderRadius: "10px", boxShadow: "rgba(0, 0, 0, 0.16) 0px 1px 4px" }}>
              <Typography variant="button" gutterBottom>
                {country.stats.activeCase}
              </Typography>
              Active Cases
            </div>
          </div>
          <Typography variant="button" gutterBottom >
            Last Updated at {split(country.updatedDate, " ")}
          </Typography>
        </CardContent>
      </CardActionArea>
      <CardActions>
        <Tooltip title={!authStatus ? subsStatus ? "Remove from email notification list" : "Add to email notification list" : "Sign Up or Login to subscribe Email Notification"} arrow>
          <div><IconButton aria-label="delete" disabled={authStatus} color="primary" onClick={() => handelSubscription(!subsStatus)}>
            {subsStatus ? <Mail /> : <MailOutlineIcon />}
          </IconButton>
          </div>
        </Tooltip>
        <Link className='link'
          to={{
            pathname: `/countrydeatil/${country.countryCode}`,
            state: { fromDashboard: true }
          }}
          >

          <Button size="small" variant="contained" color="primary">
            Learn More
          </Button></Link>
      </CardActions>
    </Card>
  );
}

SimpleCard.prototype = {
  country: PropTypes.object
}