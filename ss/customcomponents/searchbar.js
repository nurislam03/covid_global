/* eslint-disable no-use-before-define */
import React from 'react';
import TextField from '@material-ui/core/TextField';
import {Avatar} from '@material-ui/core';
import Autocomplete from '@material-ui/lab/Autocomplete';
import { makeStyles } from '@material-ui/core/styles';

// ISO 3166-1 alpha-2
// ⚠️ No support for IE 11


const useStyles = makeStyles({
  option: {
    fontSize: 15,
    '& > span': {
      marginRight: 10,
      fontSize: 18,
    },
  },
  popupIndicator: {
    "& span": {
      "& svg": {
        "& path": {
          d: "path('M15.5 14h-.79l-.28-.27C15.41 12.59 16 11.11 16 9.5 16 5.91 13.09 3 9.5 3S3 5.91 3 9.5 5.91 16 9.5 16c1.61 0 3.09-.59 4.23-1.57l.27.28v.79l5 4.99L20.49 19l-4.99-5zm-6 0C7.01 14 5 11.99 5 9.5S7.01 5 9.5 5 14 7.01 14 9.5 11.99 14 9.5 14z')" // your svg icon path here
        }
      }
    }
  }
});

export default function CountrySelect( {searchvalue,countries } ) {
  const classes = useStyles();

  return (
    <Autocomplete
      id="country-select-demo"
      style={{ width:"80%"  }}
      options={countries}
      onChange={(event, value) => searchvalue(value)}
      classes={{
        option: classes.option,
        popupIndicator: classes.popupIndicator
      }}
      autoHighlight
      getOptionLabel={(option) => option.countryName}
      renderOption={(option) => {
        let imgSrc=`${process.env.PUBLIC_URL}/SVG/${option.countryCode}.svg`
        return <React.Fragment>
          {/* <span>{countryToFlag(option.code)}</span> */}
          <span> <Avatar alt="Flage" src={imgSrc}  className={classes.small} /> </span>
          {option.countryName} ({option.countryCode}) 
        </React.Fragment>
      }}
      renderInput={(params) => (
        <TextField
          {...params}
          label="Choose a country"
          variant="outlined"
          inputProps={{
            ...params.inputProps,
            autoComplete: 'new-password', // disable autocomplete and autofill
          }}
        />
      )}
    />
  );
}
