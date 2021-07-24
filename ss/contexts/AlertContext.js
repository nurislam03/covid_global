import React, { useState } from "react";
import { Snackbar, } from '@material-ui/core';
import { Alert } from '@material-ui/lab';
import Backdrop from '@material-ui/core/Backdrop';
import CircularProgress from '@material-ui/core/CircularProgress';
import { makeStyles } from '@material-ui/core/styles';

const useStyles = makeStyles((theme) => ({
    backdrop: {
        zIndex: theme.zIndex.drawer + 1,
        color: '#fff',
    },
}));


export const AlertContext = React.createContext();

export const AlertProvider = (props) => {

    const classes = useStyles();
    // const [openalert, setopenalert] = React.useState(false)
    const [alert, setAlert] = React.useState({
        openalert: false,
        type: "",
        message: ""
    })
    let [loading, setLoading] = useState(false);

    function showAlert(type, message) {
        setAlert({ openalert: true, type: type, message: message })
    }
    function startLoader() {
        setLoading(true)
    }
    function stopLoader() {
        setLoading(false)
    }

    return (
        <AlertContext.Provider value={{ showAlert: showAlert, startLoader: startLoader, stopLoader: stopLoader }}>
            {props.children}
            <Snackbar open={alert.openalert} autoHideDuration={4000} onClose={() => setAlert({
                openalert: false,
                type: alert.type,
                message: ""
            })}>
                <Alert severity={alert.type}>
                    {alert.message}
                </Alert>
            </Snackbar>
            <Backdrop className={classes.backdrop} open={loading}>
                <CircularProgress color="inherit" />
            </Backdrop>
        </AlertContext.Provider>
    )
}