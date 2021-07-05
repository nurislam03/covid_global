import api from "../services/axiosConfig";
import countries1 from '../data/json/countries'


export const getCountriesService = async () => {
    try {
        let body =
        {
            "offset": 0,
            "limit": 0
        }

        let response = await api.post('/', body)
        if (response.data)
            return response = { data: countries1 }
    } catch (error) {

        return { data: countries1 }
        //    return {error}

    }
}
export const getSpecificCountryService = async (countryCode) => {
    try {
        let body = {
            location: countryCode
        }
        let response = await api.post(`/search`, body)
        if (response.data)
            return response = { data: response.data.info }
    } catch (error) {
        if(error.response)
        return  error.response.status
        return 404

    }
}
