import React, { useContext, useState, useEffect } from 'react'
import CountrySelect from '../customcomponents/searchbar'
import Card from '../customcomponents/card'
import { Grid } from "@material-ui/core";
import countries1 from "../data/json/countries"
import { CountryContext } from "../contexts/CountriesContext"
// import {getCountriesService} from '../services/searchService'
export default function Search() {

  const [countries] = useContext(CountryContext)
  const [thiscountries, setthisCountries] = useState([])

  const handelChange = (value) => {
    let temp = value ? countries1.filter(x => x.countryName === value.countryName) : countries
    setthisCountries(temp)
  }

  useEffect(() => {
    setthisCountries(countries)
  }, [countries])

  return (
    <div style={{ display: 'flex', width: "100%", height: "82%", flexDirection: "column", alignItems: "center" }} >
      <div style={{ display: 'flex', width: "100%", justifyContent: "center", marginTop: "10px", marginBottom: "20px" }}>
        <CountrySelect searchvalue={handelChange} countries={countries} />
      </div>
      <div style={{ overflowX: "hidden", width: '100%', marginBottom: "10px", paddingTop: "5px" }}>
        <Grid container justify="center" spacing={2} wrap="wrap">
          {thiscountries.map((item1, index) => {
            return <Grid item key={index} >
              <Card country={item1} />
            </Grid>
          })}
        </Grid>
      </div>
    </div>

  )
}

