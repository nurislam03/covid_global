import React, { useEffect } from "react";
import countries1 from "../data/json/countries"
import { getCountriesService } from '../services/searchService'


export const CountryContext = React.createContext();

export const CountriesProvider = (props) => {

    const [countries, setCountries] = React.useState([])
    // const [showSubs, setShowsubs] = React.useState(false)
    useEffect(async () => {
        let res = await getCountriesService()
        if(res.error) return
        if (res.data.length) {
            setCountries(res.data)
        }

    }, [])

    return (
        <CountryContext.Provider value={[countries, setCountries]}>
            {props.children}
        </CountryContext.Provider>
    )
}