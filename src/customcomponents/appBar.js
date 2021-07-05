import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import IconButton from '@material-ui/core/IconButton';
import AccountCircle from '@material-ui/icons/AccountCircle';
import MenuItem from '@material-ui/core/MenuItem';
import Menu from '@material-ui/core/Menu';
import PropTypes from 'prop-types';
import Button from "@material-ui/core/Button";
import { Link } from 'react-router-dom';
import { AuthContext } from "../contexts/AuthContext"
import { AlertContext } from "../contexts/AlertContext"
import { LogOutService } from "../services/authService";
import { useHistory } from 'react-router-dom';




const useStyles = makeStyles((theme) => ({
  root: {
    flexGrow: 1,
  },
  menuButton: {
    marginRight: theme.spacing(2),
  },
  title: {
    flexGrow: 1,
  },
}));

export default function MenuAppBar({ titel }) {
  const classes = useStyles();
  const [anchorEl, setAnchorEl] = React.useState(null);
  const open = Boolean(anchorEl);
  const [auth, setAuth, showSubs, setShowsubs] = React.useContext(AuthContext)
  const value = React.useContext(AlertContext)
  const history = useHistory();
 
  const handleMenu = (event) => {
    setAnchorEl(event.currentTarget);
  };

  const handleClose = () => {
    setAnchorEl(null);
  };

  const handleLogOut = async () => {
    try {
      value.startLoader()
      let body={
        sessionID:auth.sessionID
      }
      await LogOutService(body)
      value.stopLoader()
      value.showAlert("success", "Loged Out Sucessfully")
      setAnchorEl(null);
      setAuth({
        name: "",
        subscriptions: [],
        email: "",
        sessionID: ""
      })
      setShowsubs(false)
      history.push("/")
     

    } catch (error) {
      value.showAlert("error", "Loging Out Failled")

     
    }

  };
  const handleSubsRoute = () => {
    if (!showSubs) {
      if(auth.subscriptions.length){
      history.push("/subscribed")
      setShowsubs(true)}
      else{
      value.showAlert("warning", "You have not subscribed any country yet.")

      }
    }
    else {
      history.push("/")
      setShowsubs(false)

    }

  };

  return (
    <div className={classes.root}>
      <AppBar position="static">
        <Toolbar>

         
          <Typography variant="h6" className={classes.title}>
            <Link className="link"
              to={{
                pathname: "/"
              }}>{titel}
            </Link>
          </Typography>

          {auth.sessionID !== "" ? (
            <div>
              <IconButton
                aria-label="account of current user"
                aria-controls="menu-appbar"
                aria-haspopup="true"
                onClick={handleMenu}
                color="inherit"
              >
                <AccountCircle />
                {auth.name}
              </IconButton>
              <Menu
                id="menu-appbar"
                anchorEl={anchorEl}
                anchorOrigin={{
                  vertical: 'top',
                  horizontal: 'right',
                }}
                keepMounted
                transformOrigin={{
                  vertical: 'top',
                  horizontal: 'right',
                }}
                open={open}
                onClose={handleClose}
              >
                <MenuItem style={{borderBottom:"solid",borderBottomColor:"#c4c4c4",borderBottomWidth:1}}>{auth.email}</MenuItem>
                <MenuItem onClick={handleSubsRoute}>{showSubs ? 'All Countries' : 'Subscription List'}</MenuItem>
                <MenuItem onClick={handleLogOut}>Log Out</MenuItem>
              </Menu>
            </div>
          ) : (
            <div>
              {window.location.pathname !== '/signin' &&
                <Link className='link'
                  to={{
                    pathname: "/signin",
                    state: { fromDashboard: true }
                  }}>

                  <div>
                    <Button color="secondary" variant="contained">Login/SignUp</Button>
                  </div></Link>}
            </div>
          )}
        </Toolbar>
      </AppBar>
    </div>
  );
}

MenuAppBar.prototype = {
  titel: PropTypes.string
}