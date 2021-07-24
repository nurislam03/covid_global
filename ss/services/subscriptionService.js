import api from "../services/axiosConfig";

 
 export const Subscribe = async(body)=>{
       try {
           let response= await api.post('/registernotification',body)
           return response
       } catch (error) {
           return {error}
           
       }
 }
 export const Unsubscribe = async(body)=>{
       try {
       
           let response= await api.post('/unregisternotification',body)
           return response
       } catch (error) {
          
           return {error}
           
       }
 }
 