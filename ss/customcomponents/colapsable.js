import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Accordion from '@material-ui/core/Accordion';
import AccordionSummary from '@material-ui/core/AccordionSummary';
import AccordionDetails from '@material-ui/core/AccordionDetails';
import Typography from '@material-ui/core/Typography';
import ExpandMoreIcon from '@material-ui/icons/ExpandMore';
import Modal from '../customcomponents/modal'
// import '@fontsource/roboto';

const useStyles = makeStyles((theme) => ({
       
    root: {
        width: '98%',
        marginBottom:'8px'
    },
    heading: {
        fontSize: theme.typography.pxToRem(15),
        flexBasis: '31.33%',
        flexShrink: 0
    },
    secondaryHeading: {
        fontSize: theme.typography.pxToRem(15),
        color: theme.palette.text.secondary,
    },
}));

export default function Colapsable({ detail }) {
    const classes = useStyles();
    const [ha, setha] = React.useState(false)
    const hand = () => {
        setha(!ha)
    }

    return (
        <div className={classes.root}>
            <Accordion>
                <AccordionSummary
                    expandIcon={<ExpandMoreIcon />}
                    aria-controls="panel1a-content"
                    id="panel1a-header"
                >
                    <Typography className={classes.heading}>{detail.titel}</Typography>
                    <Typography className={classes.secondaryHeading}>{detail.highlite}</Typography>
                </AccordionSummary>
                <AccordionDetails style={{ display: "flex", flexDirection: "column" }} >

                    <p style={{ textOverflow: 'ellipsis', display: 'block', overflow: 'hidden', lineBreak: 'auto', maxLines: '2', whiteSpace: 'nowrap', width: "90%" }}> {detail.summary}</p>
                    <p style={{ color: "blue" }} onClick={() =>  hand()  }>
                        see more
                    </p>

                </AccordionDetails>
            </Accordion>
            <Modal handelarTag={ha} onClose={hand} titel={detail.titel} body={detail.summary}/>
        </div>
    );
}




