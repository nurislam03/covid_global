import React from 'react';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import { Container } from '@material-ui/core';

export default function Footer() {
    return (
        <AppBar position="static" color="primary">
          <Container maxWidth="md">
            <Toolbar style={{justifyContent:"center", alignItems:"center"}} >
              <Typography variant="body1" color="inherit">
                © 2021 FUAS-HIS-SCS-Group C
              </Typography>
            </Toolbar>
          </Container>
        </AppBar>
    )
}