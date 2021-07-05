import './App.css';
import MenuAppBar from './customcomponents/appBar'
import Footer from './customcomponents/footer'
import SearchScreen from './screens/search'
import React from 'react';
import CountryDetail from '../src/screens/countryDetail'
import SignInSide from '../src/screens/signin'
import Sublist from '../src/screens/subscriptionList'
import { Route, Switch } from 'react-router-dom';
import {CountriesProvider} from "./contexts/CountriesContext"
import {AuthProvider} from "./contexts/AuthContext"
import {AlertProvider} from "./contexts/AlertContext"



function App() {
   
  
  return (
<CountriesProvider>
<AuthProvider>
<AlertProvider>
    <div style={{ display: 'flex', height: "100vh", width: "100%", flexDirection: "column", backgroundColor: "whitesmoke" }}>

      <MenuAppBar titel="C.T. A" />
      <Switch>
      <Route exact path='/' component={SearchScreen} />
      <Route path='/countrydeatil/:countryid' component={CountryDetail} />
      <Route path='/signin' component={SignInSide} />
      <Route path='/subscribed' component={Sublist} />
      </Switch>
      <Footer />
    </div>
    </AlertProvider>
    </AuthProvider>
    </CountriesProvider>

  )

}

export default App;
