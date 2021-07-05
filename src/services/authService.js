import api from "../services/axiosConfig";

 
 export const SignInService = async(body)=>{
       try {
           let response= await api.post('/login',body)
          if(response.data)
           return response.data
       } catch (error) {
          
           return {error}
           
       }
 }
 export const SignUpService = async(body)=>{
       try {
           let response= await api.post('/register',body)
      
           return response
           
       } catch (error) {

           return {error}
           
       }
 }
 export const LogOutService = async(body)=>{
       try {
        //    console.log(body);
           let response= await api.post('/logout',body)
          if(response)
          localStorage.removeItem('auth')
           return response
       } catch (error) {
          
           return {error}
           
       }
 }