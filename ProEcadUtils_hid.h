/*-----------------------------------------------------------------------------
   Date   Version   Author  Vers  Comment
--------- -------  -------- ----- ---------------------------------------------
05-Jun-17 P-30-44  Asher    $$1   Created.
-----------------------------------------------------------------------------*/

#ifndef PROECADUTILS_HID_H_
#define PROECADUTILS_HID_H_

#include <ProMdl.h>
#include <ProSizeConst.h>

typedef enum {
   PRO_TK_ECAD_IDX
  ,PRO_TK_ECAD_EDA
} ProTKEcadType;

typedef void* ProEcadImpOpts;

typedef void* ProEcadExpOpts;


PRO_BEGIN_C_DECLS


extern ProError ProEcadImport(ProPath         filename,
                              ProEcadImpOpts  options,
                              ProTKEcadType   ecad_type,
                              ProMdl         *r_new_model);
/*
ProEcadImport


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadImport" when you submit this file.

   Input Arguments:
       filename:            <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       options:             <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       ecad_type:           <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle

   Output Arguments:
       r_new_model:         <ALLOWED_TO_BE_NULL> No
                            <POINTER_TYPE> Handle
*/
/*
  Purpose: Import an EDMD design to specified type

  Input Arguments:
     filename        - Name of the EDMD file to be imported.
     options         - Import options.
     ecad_type       - The type of the imported file.

  Output Arguments:
     r_new_model     - The new assembly that Creo Parametric created.

  Return Values:
     PRO_TK_NO_ERROR      - Import finished successfully.
     PRO_TK_INVALID_NAME  - The file name is NULL or
                            extension of file name is invalid
     PRO_TK_INVALID_DIR   - The directory of file name is invalid
     PRO_TK_EMPTY         - The file is empty.
     PRO_TK_UNSUPPORTED   - ecad_type is not supported.
     PRO_TK_USER_ABORT    - Used in collaboration mode.
     PRO_TK_BAD_INPUTS    - One of the inputs has bad value which
                            is not of the above errors.
     PRO_TK_GENERAL_ERROR - Import failed for any other reason.
*/




extern ProError ProEcadExport(ProPath               filename,
                              ProEcadExpOpts        options,
                              ProTKEcadType         ecad_type,
                              ProMdl                assem_model);
/*
ProEcadExport


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadExport" when you submit this file.

   Input Arguments:
       filename:            <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       options:             <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       ecad_type:           <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       assem_model:         <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle

   Output Arguments:
      None
*/
/*
  Purpose: Export ECAD Assembly design into EDMD or EDA format.

  Input Arguments:
     filename        - Name of the output IDX or EDA file.
     options         - Reserved for future expansion. Pass NULL.
     ecad_type       - The type of the exported file.
     assem_model     - The assembly to be exported.

  Return Values:
     PRO_TK_NO_ERROR        - Export finished successfully.
     PRO_TK_INVALID_NAME    - The file name is NULL or
                              extension of file name is invalid
     PRO_TK_INVALID_DIR     - The directory of file name is invalid or
                              is read only
     PRO_TK_UNSUPPORTED     - ecad_type is not supported.
     PRO_TK_NOT_IMPLEMENTED - options parameter is not NULL.
     PRO_TK_USER_ABORT      - Used in collaboration mode.
     PRO_TK_BAD_INPUTS      - One of the inputs has bad value which
                              is not of the above errors.
     PRO_TK_GENERAL_ERROR   - Export failed for any other reason.
*/


extern ProError ProEcadImpOptsAlloc( ProEcadImpOpts *options );
/*
ProEcadImpOptsAlloc


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadImpOptsAlloc" when you submit this file.

   Input Arguments:
      None

   Output Arguments:
       options:             <ALLOWED_TO_BE_NULL> No
                            <POINTER_TYPE> Handle
*/
/*
  Purpose:
     Allocates the handle for a <i>ProEcadImpOpts</i> data structure.

  Input Arguments:
     None

  Output Arguments:
     options   - The pointer to the handle for the <i>ProEcadImpOpts</i> 
                 structure. You should free this memory when you are 
                 done using it.

  Return Values:

     PRO_TK_NO_ERROR   - The function successfully allocated the handle.
     PRO_TK_BAD_INPUTS - if input is NULL pointer 
*/

extern ProError ProEcadImpOptsFree( ProEcadImpOpts *options );
/*
ProEcadImpOptsFree


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadImpOptsFree" when you submit this file.

   Input Arguments:
       options:             <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle

   Output Arguments:
      None
*/
/*
  Purpose:
     Releases the handle to the <i>ProEcadImpOpts</i> data structure.

  Input Arguments:
     options   - The pointer to the handle for the <i>ProEcadImpOpts</i>

  Output Arguments:
     None

  Return Values:
    
     PRO_TK_NO_ERROR   - The function successfully freed the handle.
     PRO_TK_BAD_INPUTS - if input is NULL pointer 

*/

extern ProError ProEcadImpOptsFlexDesignSet (ProEcadImpOpts options,
                                             ProBoolean     flex_design);
/*
ProEcadImpOptsFlexDesignSet


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadImpOptsFlexDesignSet" when you submit this file.

   Input Arguments:
       options:             <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle
       flex_design:         <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle

   Output Arguments:
      None
*/
/*
  Purpose:
     Sets the import options to be according to flexible or rigid PCB design
     needs.

  Input Arguments:
     options      - The pointer to the handle for the <i>ProEcadImpOpts</i>
     flex_design  - Import the PCB design as flexible (PRO_B_TRUE) or as
                    Rigid (PRO_B_FALSE)

  Output Arguments:
     None

  Return Values:
     PRO_TK_NO_ERROR    - The function successfully set the options.
     PRO_TK_BAD_INPUTS  - One or more input arguments is invalid.
*/

extern ProError ProEcadImpOptsFlexDesignGet (ProEcadImpOpts  options,
                                             ProBoolean     *r_flex_design);
/*
ProEcadImpOptsFlexDesignGet


DO NOT CHANGE THIS COMMENT IN ANY WAY!!

Add documentation AFTER this comment. There should be two \separate/
comments for "ProEcadImpOptsFlexDesignGet" when you submit this file.

   Input Arguments:
       options:             <ALLOWED_TO_BE_NULL> Yes
                            <POINTER_TYPE> Handle

   Output Arguments:
       r_flex_design:       <ALLOWED_TO_BE_NULL> No
                            <POINTER_TYPE> Handle
*/
/* 
  Purpose:
     Collect the current options settings to check if they are according to
     flexible PCB design needs.

  Input Arguments:
     options     - The pointer to the handle for the <i>ProEcadImpOpts</i>.

  Output Arguments:
     r_flex_design  - The current import options settings match/do not match
                      flexible PCB design.

  Return Values:
     PRO_TK_NO_ERROR      - The function successfully retrieved the information.
     PRO_TK_BAD_INPUTS    - One or more input arguments is invalid.
*/


PRO_END_C_DECLS

#endif /* PROECADUTILS_HID_H_ */
