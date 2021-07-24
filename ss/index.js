import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import { HashRouter } from "react-router-dom";
import reportWebVitals from './reportWebVitals';

ReactDOM.render(
  // <React.StrictMode>
  // <BrowserRouter>
  <HashRouter>
  <App />
  </HashRouter>
  // </BrowserRouter>
  // </React.StrictMode>,
  ,document.getElementById('root')
);
reportWebVitals();
