import React, { useContext } from 'react'
import Card from '../customcomponents/card'
import { Grid } from "@material-ui/core";
import { CountryContext } from "../contexts/CountriesContext"
import { AuthContext } from "../contexts/AuthContext"

export default function Sublist() {
 

  const [countries, ] = useContext(CountryContext)
  const [auth] = useContext(AuthContext)

  // useEffect(() => {
  //   if (!auth.subsribedCountries.length && showSubs) {
  //     setShowsubs(false)
  //     history.push("/")
  //   }
  // }, [auth])


  return (
    <div style={{ display: 'flex', width: "100%", height: "82%", flexDirection: "column", alignItems: "center" }} >
      {/* <div style={{ display: 'flex', width: "100%", justifyContent: "center", marginTop: "10px", marginBottom: "20px" }}>
        <CountrySelect searchvalue={handelChange} countries={countries1} />
      </div> */}
      <div style={{ overflowX: "hidden", width: '100%', marginBottom: "10px", paddingTop: "5px" }}>
        {auth.subscriptions.length && <Grid container justify="center" spacing={2} wrap="wrap">
          {countries.map((item1, index) => {
            if (auth.subscriptions.includes(item1.countryCode)){
              return <Grid item key={index} >
                <Card country={item1} />
              </Grid>
            }
            return {}
          })}
        </Grid>}
        {/* <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam eget ex tellus. In hac habitasse platea dictumst. Vestibulum quis interdum dolor. Aliquam eget tincidunt ex, sit amet pellentesque augue. Nullam facilisis eros justo, at rhoncus metus aliquam sollicitudin. Nunc convallis nisl vel consequat sodales. Nam vitae sapien semper, euismod enim a, suscipit urna. Suspendisse et urna eu mi laoreet fermentum a ut nulla. Cras ipsum magna, lobortis et tortor sed, aliquet egestas lacus. Etiam sit amet pretium velit, eu eleifend dolor.</p> */}
      </div>
    </div>

  )
}

