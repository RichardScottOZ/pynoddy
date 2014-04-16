/*
	This file was generated by XVT-Design 4.5, a product of:

		XVT Software Inc.
		4900 Pearl East Circle
		Boulder, CO USA 80301
		303-443-4223, fax 303-443-0969

	Generated on Tue Sep 02 10:35:00 1997
*/
/* TAG BEGIN SPCL:Pre_Header */
/* TAG END SPCL:Pre_Header */

#include "xvt.h"
#include "xvtcm.h"
#include "nodInc.h"

/* 
	Information about the window
*/
#define WIN_RES_ID LAYER_DISPLAY_WINDOW
#define WIN_FLAGS 0x810L
#define WIN_CLASS ""
#define WIN_BORDER W_DOC
/* TAG BEGIN SPCL:Obj_Decl */
/* TAG END SPCL:Obj_Decl */

/*
	Handler for window LAYER_DISPLAY_WINDOW ("Block Options")
*/
long XVT_CALLCONV1
#if XVT_CC_PROTO
LAYER_DISPLAY_WINDOW_eh XVT_CALLCONV2 (WINDOW xdWindow, EVENT *xdEvent)
#else
LAYER_DISPLAY_WINDOW_eh XVT_CALLCONV2 (xdWindow, xdEvent)
WINDOW xdWindow;
EVENT *xdEvent;
#endif
{
	short xdControlId = xdEvent->v.ctl.id;
	/* TAG BEGIN SPCL:Var_Decl */
	static short mouseDown = FALSE;
	/* TAG END SPCL:Var_Decl */

	switch (xdEvent->type) {
	case E_CREATE:
		/*
			Window has been created; first event sent to newly-created
			window.
		*/
		{
		/* TAG BEGIN EVNT:Create */
		loadBlockImageOptions (xdWindow);
#if (XVTWS != MACWS)
		{
		   SLIST winList;
		   SLIST_ELT element;
		   WINDOW win;
		   WIN_TYPE winType;
		                           /* disable all other windows */
		   winType = xvt_vobj_get_type(xdWindow);
		   if (winType == W_DBL)
		   {
		      if (winList = xvt_scr_list_wins ())
		      {
		         for (element = xvt_slist_get_first(winList); element != NULL;
		                                    element = xvt_slist_get_next (winList, element))
		         {
		            xvt_slist_get (winList, element, (long *) &win);
		            if (win != xdWindow)      /* disable all windows but this one */
		               xvt_vobj_set_enabled (win, FALSE);
		         }
		         xvt_slist_destroy (winList);
		      }
		   }
		}
#endif
		/* TAG END EVNT:Create */
		}
		break;
	case E_DESTROY:
		/*
			Window has been closed; last event sent to window.
		*/
		xdRemoveHelpAssoc( xdWindow );
		{
		/* TAG BEGIN EVNT:Destroy */
#if (XVTWS != MACWS)
		{
		   SLIST winList;
		   SLIST_ELT element;
		   WINDOW win;
		   WIN_TYPE winType;
		                           /* disable all other windows */
		   winType = xvt_vobj_get_type(xdWindow);
		   if (winType == W_DBL)
		   {
		      if (winList = xvt_scr_list_wins ())
		      {
		         for (element = xvt_slist_get_first(winList); element != NULL;
		                                    element = xvt_slist_get_next (winList, element))
		         {
		            xvt_slist_get (winList, element, (long *) &win);
		            if (win != xdWindow)      /* disable all windows but this one */
		               xvt_vobj_set_enabled (win, TRUE);
		         }
		         xvt_slist_destroy (winList);
		      }
		   }
		}
#endif
		/* TAG END EVNT:Destroy */
		}
		break;
	case E_FOCUS:
		{
		/* TAG BEGIN EVNT:Focus */
		/*
			Window has lost or gained focus.
		*/
		if (xdEvent->v.active)  {
			/*
				Window has gained focus
			*/
		} else {
			/*
				Window has lost focus
			*/
#if (XVTWS == MACWS)
#else
		/*
			if (W_DBL == xvt_vobj_get_type(xdWindow))
				xvt_vobj_destroy (xdWindow);
		*/
#endif
		}
		/* TAG END EVNT:Focus */
		}
		break;
	case E_SIZE:
		/*
			Size of window has been set or changed; sent when window is
			created or subsequently resized by user or via xvt_vobj_move.
		*/
		{
		/* TAG BEGIN EVNT:Size */
		/* TAG END EVNT:Size */
		}
		break;
	case E_UPDATE:
		/*
			Window requires updating.
		*/
		{
		/* TAG BEGIN EVNT:Update */
		BLOCK_DIAGRAM_DATA *diagram = (BLOCK_DIAGRAM_DATA *) xvt_vobj_get_data(xdWindow);
		xvt_dwin_clear(xdWindow, (COLOR)xvt_vobj_get_attr(xdWindow, ATTR_BACK_COLOR));
		if (diagram)
		   drawBlockImageColorScale (xdWindow, diagram->lut, NULL, FALSE);
		/* TAG END EVNT:Update */
		}
		break;
	case E_CLOSE:
		/*
			Request to close window; user operated "close" menu item on
			window system menu, or operated "close" control on window
			frame. Not sent if Close on File menu is issued. Window not
			closed unless xvt_vobj_destroy is called.
		*/
		{
		/* TAG BEGIN EVNT:Close */
		xvt_vobj_destroy(xdWindow);
		/* TAG END EVNT:Close */
		}
		break;
	case E_CHAR:
		/*
			Character typed.
		*/
		{
		/* TAG BEGIN EVNT:Char */
			/* *********************************************** */
			/* make a RETURN key activate the window OK Button */
		if (xdEvent->v.chr.ch == '\r')
		{
		   xdEvent->type = E_CONTROL;
		   xdEvent->v.ctl.id = LAYER_DISPLAY_OK;
		   xvt_win_dispatch_event (xdWindow, xdEvent);
		}
		/* TAG END EVNT:Char */
		}
		break;
	case E_MOUSE_UP:
		/*
			Mouse was released
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Up */
		setBlockImageColorIndex (xdWindow, &(xdEvent->v.mouse.where), NULL, NULL);
		xvt_win_release_pointer ();
		mouseDown = FALSE;
		/* TAG END EVNT:Mouse_Up */
		}
		break;
	case E_MOUSE_DOWN:
		/*
			Mouse was pressed
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Down */
		mouseDown = TRUE;
		xvt_win_trap_pointer(xdWindow);
		setBlockImageColorIndex (xdWindow, &(xdEvent->v.mouse.where), NULL, NULL);
		/* TAG END EVNT:Mouse_Down */
		}
		break;
	case E_MOUSE_DBL:
		/*
			Mouse was double clicked
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Dbl */
		/* TAG END EVNT:Mouse_Dbl */
		}
		break;
	case E_MOUSE_MOVE:
		/*
			Mouse was moved
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Move */
		if (mouseDown)
		   setBlockImageColorIndex (xdWindow, &(xdEvent->v.mouse.where), NULL, NULL);
		/* TAG END EVNT:Mouse_Move */
		}
		break;
	case E_HSCROLL:
		{
		/* TAG BEGIN EVNT:Hscroll */
		/*
			Horizontal scrollbar on frame was operated
		*/
		switch (xdEvent->v.scroll.what) {
		case SC_LINE_UP:
			break;
		case SC_LINE_DOWN:
			break;
		case SC_PAGE_UP:
			break;
		case SC_PAGE_DOWN:
			break;
		case SC_THUMB:
			break;
		case SC_THUMBTRACK:
			break;
		default:
			break;
		}
		/* TAG END EVNT:Hscroll */
		}
		break;
	case E_VSCROLL:
		{
		/* TAG BEGIN EVNT:Vscroll */
		/*
			Vertical scrollbar on frame was operated
		*/
		switch (xdEvent->v.scroll.what) {
		case SC_LINE_UP:
			break;
		case SC_LINE_DOWN:
			break;
		case SC_PAGE_UP:
			break;
		case SC_PAGE_DOWN:
			break;
		case SC_THUMB:
			break;
		case SC_THUMBTRACK:
			break;
		default:
			break;
		}
		/* TAG END EVNT:Vscroll */
		}
		break;
	case E_COMMAND:
		/*
			User issued command on window menu bar (menu bar at top of
			screen for Mac/CH).
		*/
		{
		/* TAG BEGIN EVNT:Command */
		/*
			No menubar was associated with this window
		*/
		/* TAG END EVNT:Command */
		}
		break;
	case E_CONTROL:
		/*
			User operated control in window.
		*/
		{
		/* TAG BEGIN SPCL:Control_Decl */
		/* TAG END SPCL:Control_Decl */

		switch(xdControlId) {
		case LAYER_DISPLAY_LIST: /* "Layer List" */
			{
			/* TAG BEGIN LAYER_DISPLAY_LIST EVNT:Control */
			/*
				List box was operated.
			*/
			if (xdEvent->v.ctl.ci.v.lbox.dbl_click) {
				/*
					double click
				*/
			} else {
				/*
					single click
				*/
				xvt_dwin_invalidate_rect(xdWindow, (RCT *) NULL);
			}
			/* TAG END LAYER_DISPLAY_LIST EVNT:Control */
			}
			break;
		case LAYER_DISPLAY_TYPE: /* "Block Type" */
			{
			/* TAG BEGIN LAYER_DISPLAY_TYPE EVNT:Control */
			updateBlockImageOptions (xdWindow);
			/* TAG END LAYER_DISPLAY_TYPE EVNT:Control */
			}
			break;
		case LAYER_RESET_COLORS: /* "Reset" */
			{
			/* TAG BEGIN LAYER_RESET_COLORS EVNT:Control */
			BLOCK_DIAGRAM_DATA *display = (BLOCK_DIAGRAM_DATA *) xvt_vobj_get_data(xdWindow);
			destroy1DArray ((char *) display->lut);
			display->lut = (COLOR *) NULL;
			display->lutSize = 0;
			updateBlockImageOptions (xdWindow);
			/* TAG END LAYER_RESET_COLORS EVNT:Control */
			}
			break;
		case LAYER_EDIT_COLORS: /* "Edit..." */
			{
			/* TAG BEGIN LAYER_EDIT_COLORS EVNT:Control */
			/* TAG END LAYER_EDIT_COLORS EVNT:Control */
			}
			break;
		case LAYER_CALC_VALUES: /* "Calc Real Values" */
			{
			/* TAG BEGIN LAYER_CALC_VALUES EVNT:Control */
			extern int noStatusWin;
			BLOCK_DIAGRAM_DATA *diagram = (BLOCK_DIAGRAM_DATA *) xvt_vobj_get_data (xdWindow);
			int dataType;
			switch (xvt_list_get_sel_index (xvt_win_get_ctl (xdWindow, LAYER_DISPLAY_TYPE)))
			{
			   case (2): /* Density */
			      dataType = DENSITY_BLOCK;      
			      break;
			   case (3): /* Sus X */
			      dataType = SUS_X_BLOCK;      
			      break;
			   case (4): /* Sus Y */
			      dataType = SUS_Y_BLOCK;      
			      break;
			   case (5): /* Sus Z */
			      dataType = SUS_Z_BLOCK;      
			      break;
			   case (6): /* Sus Dip */
			      dataType = SUS_DIP_BLOCK;      
			      break;
			   case (7): /* Sus Dip Direction */
			      dataType = SUS_DDIR_BLOCK;
			      break;
			   case (8): /* Sus Pitch */
			      dataType = SUS_PITCH_BLOCK;      
			      break;
			   case (9): /* Rem Intensity */
			      dataType = REM_STR_BLOCK;      
			      break;
			   case (10): /* Rem Inclination */
			      dataType = REM_INC_BLOCK;
			      break;
			   case (11): /* Rem Declination */
			      dataType = REM_DEC_BLOCK;
			      break;
			   default:
			      return 0L;
			}
			noStatusWin = TRUE;
			calcBlockImageValueData(diagram, dataType);
			noStatusWin = FALSE;
			updateBlockImageOptions(xdWindow);
			/* TAG END LAYER_CALC_VALUES EVNT:Control */
			}
			break;
		case LAYER_DISPLAY_ALL: /* "All Layers (Solid Block)" */
			{
			/* TAG BEGIN LAYER_DISPLAY_ALL EVNT:Control */
			WINDOW ctl_win = xvt_win_get_ctl(xdWindow, LAYER_DISPLAY_ALL);
			xvt_ctl_set_checked(ctl_win, (BOOLEAN) (!xvt_ctl_is_checked (ctl_win)));
			updateBlockImageOptions(xdWindow);
			/* TAG END LAYER_DISPLAY_ALL EVNT:Control */
			}
			break;
		case LAYER_LUT_START: /* "start" */
			{
			/* TAG BEGIN LAYER_LUT_START EVNT:Control */
			/*
				Edit control was operated.
			*/
			if (xdEvent->v.ctl.ci.v.edit.focus_change) {
				if (xdEvent->v.ctl.ci.v.edit.active) {
					/*
						focus has entered the control
					*/
				} else {
					/*
						focus has left the control
					*/
				}
			} else {
				/*
					Contents of control were changed
				*/
				double value;
				value = getFloatTextFieldValue (xdWindow, LAYER_LUT_START) - 1.0;
				setBlockImageColorIndex (xdWindow, NULL, &value, NULL);
			}
			/* TAG END LAYER_LUT_START EVNT:Control */
			}
			break;
		case LAYER_LUT_END: /* "end" */
			{
			/* TAG BEGIN LAYER_LUT_END EVNT:Control */
			/*
				Edit control was operated.
			*/
			if (xdEvent->v.ctl.ci.v.edit.focus_change) {
				if (xdEvent->v.ctl.ci.v.edit.active) {
					/*
						focus has entered the control
					*/
				} else {
					/*
						focus has left the control
					*/
				}
			} else {
				/*
					Contents of control were changed
				*/
				double value;
				value = getFloatTextFieldValue (xdWindow, LAYER_LUT_END) - 1.0;
				setBlockImageColorIndex (xdWindow, NULL, NULL, &value);
			}
			/* TAG END LAYER_LUT_END EVNT:Control */
			}
			break;
		case LAYER_DISPLAY_OK: /* "OK" */
			{
			/* TAG BEGIN LAYER_DISPLAY_OK EVNT:Control */
			saveBlockImageOptions (xdWindow, (BLOCK_DIAGRAM_DATA *) xvt_vobj_get_data(xdWindow));
			/* TAG END LAYER_DISPLAY_OK EVNT:Control */
			}
			break;
		case LAYER_DISPLAY_HELP: /* "Help..." */
			{
			/* TAG BEGIN LAYER_DISPLAY_HELP EVNT:Control */
			displayHelp("blockop.htm");
			/* TAG END LAYER_DISPLAY_HELP EVNT:Control */
			}
			break;
		case LAYER_DISPLAY_CANCEL: /* "Cancel" */
			{
			/* TAG BEGIN LAYER_DISPLAY_CANCEL EVNT:Control */
			xvt_vobj_destroy(xdWindow);
			/* TAG END LAYER_DISPLAY_CANCEL EVNT:Control */
			}
			break;
		case LAYER_LUT_STRETCH: /* "stretch" */
			{
			/* TAG BEGIN LAYER_LUT_STRETCH EVNT:Control */
			/* TAG END LAYER_LUT_STRETCH EVNT:Control */
			}
			break;
		default:
			break;
		}
		}
		break;
	case E_FONT:
		/*
			User issued font command on window menu bar (menu bar at top of
			screen for Mac/CH).
		*/
		{
		/* TAG BEGIN EVNT:Font */
		/* TAG END EVNT:Font */
		}
		break;
	case E_TIMER:
		/*
			Timer associated with window went off.
		*/
		{
		/* TAG BEGIN EVNT:Timer */
		/* TAG END EVNT:Timer */
		}
		break;
	case E_USER:
		/*
			Application initiated.
		*/
		{
		/* TAG BEGIN EVNT:User */
		switch (xdEvent->v.user.id) {
		case -1:
		default:
			break;
		}
		/* TAG END EVNT:User */
		}
		break;
	default:
		break;
	}
	/* TAG BEGIN SPCL:Bottom */
#ifdef XVT_R40_TXEDIT_BEHAVIOR
	xvt_tx_process_event(xdWindow, xdEvent);
#endif
	/* TAG END SPCL:Bottom */
	return 0L;
}