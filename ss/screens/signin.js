import React from 'react';
import clsx from 'clsx';
import Avatar from '@material-ui/core/Avatar';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import Link from '@material-ui/core/Link';
import Paper from '@material-ui/core/Paper';
import Box from '@material-ui/core/Box';
import Grid from '@material-ui/core/Grid';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import HowToRegIcon from '@material-ui/icons/HowToReg';
import { SignInService, SignUpService } from '../services/authService'
import { useHistory } from 'react-router-dom';
import { AuthContext } from '../contexts/AuthContext';
import { AlertContext } from '../contexts/AlertContext';
import { Visibility, VisibilityOff } from '@material-ui/icons';
import IconButton from '@material-ui/core/IconButton';
import OutlinedInput from '@material-ui/core/OutlinedInput';
import InputLabel from '@material-ui/core/InputLabel';
import InputAdornment from '@material-ui/core/InputAdornment';
import FormControl from '@material-ui/core/FormControl';

function Copyright() {
  return (
    <Typography variant="body2" color="textSecondary" align="center">
      {'Copyright © '}
      <Link color="inherit" >
        CTA
      </Link>{' '}
      {new Date().getFullYear()}
      {'.'}
    </Typography>
  );
}


const useStyles = makeStyles((theme) => ({
  root: {
    height: '100vh',
  },
  image: {
    backgroundImage: `url(${process.env.PUBLIC_URL}/covismap.jpg)`,
    backgroundRepeat: 'no-repeat',
    backgroundColor:
      theme.palette.type === 'light' ? theme.palette.grey[50] : theme.palette.grey[900],
    backgroundSize: 'cover',
    backgroundPosition: 'center',
  },
  paper: {
    margin: theme.spacing(8, 4),
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
  },
  avatar: {
    margin: theme.spacing(1),
    backgroundColor: theme.palette.secondary.main,
  },
  form: {
    width: '100%', // Fix IE 11 issue.
    marginTop: theme.spacing(1),
  },
  submit: {
    margin: theme.spacing(3, 0, 2),
  },
  margin: {
    margin: theme.spacing(1),
  },
  textField: {
    width: '25ch',
  },
}));

export default function SignInSide() {
  const classes = useStyles();
  const [screen, setScreen] = React.useState("signin")
  const [email, setEmail] = React.useState("")
  const [userName, setUser] = React.useState("")
  const [password, setPass] = React.useState("")
  const [showpassword, setshowPass] = React.useState(false)
  const [auth, setAuth] = React.useContext(AuthContext)
  const value = React.useContext(AlertContext)
  const history = useHistory();
  const handelScreenChangeToSignup = () => {
    setEmail("")
    setUser("")
    setPass("")
    setScreen("signup")
  }
  const handelScreenChangeToSignin = () => {
    setEmail("")
    setUser("")
    setPass("")
    setScreen("signin")
  }

  const validate = (type) => {
    let res = {
      value: true,
      message: ""
    }
    if (!userName && type === "signup") { res.value = false; res.message = "user name is required"; return res }
    if (!password) { res.value = false; res.message = "password is required"; return res }
    if (!email) { res.value = false; res.message = "email is required"; return res }
    if (email) {
      const re = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
      if (!re.test(String(email).toLowerCase())) {
        res.value = false; res.message = "invalide email address";
        return res
      }
    }
    return res
  }

  const handelSignin = async () => {
    let test = validate('signin');
    if (!test.value) {
      value.showAlert("error", test.message)
      return
    }
    let body = {
      email: email, password: password
    }

    value.startLoader()
    let res = await SignInService(body)
    value.stopLoader()
    if (res.error) { value.showAlert("error", `Login Failed ${res.error.response.data}`) } else {
      setAuth(res)
      localStorage.setItem('auth', JSON.stringify(res))
      console.log("ki hou");
      history.push("/")
      value.showAlert("success", "Login sucessfull")
    }

  }



  const handelSignup = async () => {
    let test = validate('signup');
    if (!test.value) {
      value.showAlert("error", test.message)
      return
    }
    let body = {
      email: email, password: password,
      name: userName
    }

    value.startLoader()
    let res = await SignUpService(body)
    value.stopLoader()
    if (res.error) { value.showAlert("error", `Singing Up Failed ${res.error.response.data}`) } else {
      let res = await SignInService(body)
      setAuth(res)
      localStorage.setItem('auth', JSON.stringify(res))
      value.showAlert("success", "Siging up success")
      history.push("/")
    }

  }

  const handleClickShowPassword = () => {
    setshowPass(!showpassword)

  }


  return (
    <Grid container component="main" className={classes.root}>

      <CssBaseline />
      <Grid item xs={false} sm={4} md={7} className={classes.image} />
      <Grid item xs={12} sm={8} md={5} component={Paper} elevation={6} square>
        <div className={classes.paper}>
          <Avatar className={classes.avatar}>
            {/* <LockOutlinedIcon />  */}
            {screen === "signup" ? <HowToRegIcon /> : <LockOutlinedIcon />}

          </Avatar>
          <Typography component="h1" variant="h5">
            {screen === "signup" ? 'Sign up' : 'Sign in'}
          </Typography>
          {screen === 'signup' ? (

            <form className={classes.form} noValidate>
              <TextField
                variant="outlined"
                margin="normal"
                required
                fullWidth
                value={email}
                id="email"
                label="Email Address"
                name="email"
                autoComplete="email"
                autoFocus
                onChange={(event) => { setEmail(event.target.value) }}
              />
              <TextField
                variant="outlined"
                margin="normal"
                required
                fullWidth
                id="userName"
                value={userName}
                label="UserName"
                name="userName"
                autoComplete="user name"
                onChange={(event) => { setUser(event.target.value) }}
                autoFocus
              />
              {/* <TextField
                variant="outlined"
                margin="normal"
                required
                fullWidth
                name="password"
                label="Password"
                value={password}

                type="text"
                id="password"
                autoComplete="current-password"
                onChange={(event) => { setPass(event.target.value) }}

              /> */}
              <FormControl className={clsx(classes.form)} variant="outlined">
              <InputLabel htmlFor="outlined-adornment-password">Password</InputLabel>
              <OutlinedInput
                id="outlined-adornment-password"
                type={showpassword ? 'text' : 'password'}
                value={password}
                onChange={(event) => { setPass(event.target.value) }}
                endAdornment={
                  <InputAdornment position="end">
                    <IconButton
                      aria-label="toggle password visibility"
                      onClick={handleClickShowPassword}
                      edge="end"
                    >
                      {showpassword ? <Visibility /> : <VisibilityOff />}
                    </IconButton>
                  </InputAdornment>
                }
                labelWidth={70}
              />
              </FormControl>
              <Button
                fullWidth
                variant="contained"
                color="primary"
                className={classes.submit}
                onClick={handelSignup}
              >
                Sign Up
              </Button>
              <Grid container>
                <Grid item>
                  <Link variant="body2" onClick={handelScreenChangeToSignin}>
                    {"Already have an account? Sign In"}
                  </Link>
                </Grid>
              </Grid>
              <Box mt={5}>
                <Copyright />
              </Box>
            </form>

          )
            : (
              <form className={classes.form} noValidate>
                <TextField
                  variant="outlined"
                  margin="normal"
                  required
                  fullWidth
                  id="email"
                  label="Email Address"
                  name="email"
                  value={email}
                  autoComplete="email"
                  autoFocus
                  onChange={(event) => { setEmail(event.target.value) }}
                />
               <FormControl className={clsx(classes.form)} variant="outlined">
              <InputLabel htmlFor="outlined-adornment-password">Password</InputLabel>
              <OutlinedInput
                id="outlined-adornment-password"
                type={showpassword ? 'text' : 'password'}
                value={password}
                onChange={(event) => { setPass(event.target.value) }}
                endAdornment={
                  <InputAdornment position="end">
                    <IconButton
                      aria-label="toggle password visibility"
                      onClick={handleClickShowPassword}
                      edge="end"
                    >
                      {showpassword ? <Visibility /> : <VisibilityOff />}
                    </IconButton>
                  </InputAdornment>
                }
                labelWidth={70}
              />
              </FormControl>
                <Button
                  fullWidth
                  variant="contained"
                  color="primary"
                  className={classes.submit}
                  onClick={handelSignin}
                >
                  Sign In
                </Button>
                <Grid container>
                  {/* <Grid item xs>
                <Link href="#" variant="body2">
                  Forgot password?
                </Link>
              </Grid> */}
                  <Grid item>
                    <Link variant="body2" onClick={handelScreenChangeToSignup}>
                      {"Don't have an account? Sign Up"}
                    </Link>
                  </Grid>
                </Grid>
                <Box mt={5}>
                  <Copyright />
                </Box>
              </form>
            )}
        </div>
      </Grid>
    </Grid>

  );
}