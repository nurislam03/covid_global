import axios  from "axios";
import {devBsseUrl} from "../conjig"

 const api = axios.create({
    baseURL:devBsseUrl,
    headers: {'Content-type': 'application/json; charset=UTF-8'}
  });
  export default api