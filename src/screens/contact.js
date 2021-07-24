// import React, { useState } from "react";
// import { MDBContainer, MDBRow, MDBCol, MDBBtn, MDBIcon } from 'mdbreact';
// import { AlertContext } from '../contexts/AlertContext';
// import { sendmail  } from "../services/authService";


// export default function FormPage()  {
// // const [name,setname]=useState("");
// // const [email,setemail]=useState("");
// // const [subject,setsub]=useState("");
// // const [mbody,setbody]=useState("");
// // const value = React.useContext(AlertContext)

// // const sendmails=async()=>{
// //   if( !name&&!email&&!subject&!body){
// //     value.showAlert("error", "Fill all the fields")
// //   }
// //   let body={
// //     subject:subject,
// //     message:`${mbody}+ \n sent from ${email} `,
// //     recipents:['alifelahikhan@gmail.com']
// //   }
// //   value.startLoader()
// //   let res= await sendmail(body)
// //   value.stopLoader()
// //   value.showAlert("success", "Your message has been sent")

// // }



// return (
// <MDBContainer>
//   <MDBRow>
//     <MDBCol md="6">
//       <form>
//         <p className="h4 text-center mb-4">Write to us</p>
//         <label htmlFor="defaultFormContactNameEx" className="grey-text">
//           Your name
//         </label>
//         <input type="text" id="defaultFormContactNameEx"  
//         // value={name}
//         //         onChange={(event) => { setname(event.target.value) }}
//                  className="form-control" />
//         <br />
//         <label htmlFor="defaultFormContactEmailEx" className="grey-text">
//           Your email
//         </label>
//         <input type="email" id="defaultFormContactEmailEx" 
//         //  value={email}
//         //         onChange={(event) => { setemail(event.target.value) }} 
//                 className="form-control" />
//         <br />
//         <label htmlFor="defaultFormContactSubjectEx" className="grey-text">
//           Subject
//         </label>
//         <input type="text" id="defaultFormContactSubjectEx"  
//         // value={subject}
//         //         onChange={(event) => { setsub(event.target.value) }} 
//                 className="form-control" />
//         <br />
//         <label htmlFor="defaultFormContactMessageEx"  
//         // value={mbody}
//         //         onChange={(event) => { setbody(event.target.value) }} 
//                 className="grey-text">
//           Your message
//         </label>
//         <textarea type="text" id="defaultFormContactMessageEx" className="form-control" rows="3" />
//         <div className="text-center mt-4">
//                   <MDBBtn color="warning"
//                   // outline onClick={()=>sendmails()}
//                   >
//                     Send
//                     <MDBIcon far icon="paper-plane" className="ml-2" />
//                   </MDBBtn>
//                 </div>
//               </form>
//             </MDBCol>
//           </MDBRow>
//         </MDBContainer>
//       )
//     }

 