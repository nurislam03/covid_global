import React  from "react";
// import countries1 from "../data/json/countries"

export const AuthContext= React.createContext();

export const AuthProvider=(props)=>{
    let storedAuth=localStorage.getItem('auth')
    storedAuth=storedAuth?JSON.parse(storedAuth):null
    // storedAuth=null
    const [showSubs, setShowsubs] = React.useState(false)
    const [auth, setAuth] = React.useState(storedAuth?storedAuth:{
        name:"",
        subscriptions:[],
        sessionID:"",
        email:""
    })

    return(
        <AuthContext.Provider value={[auth,setAuth,showSubs, setShowsubs]}>
            {props.children}
        </AuthContext.Provider>
    )
}