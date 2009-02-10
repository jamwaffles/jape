//--------------------------------------------------------------------------
/// \file	font.h
/// \author	Rob Bateman [robthebloke@hotmail.com]
/// \date	8-3-2005
/// \brief	
///	\note
/// 
//--------------------------------------------------------------------------

#ifndef __font__H_
#define __font__H_

#ifdef WIN32
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/// for some reason glut fonts are void pointers, dont ask me why...
	typedef void* font;

	//--------------------------------------------------------------------------
	/// \brief	sets the current font to use for rendering of text
	/// \param	f	-	One of the following constants
	/// 
	///					GLUT_BITMAP_9_BY_15		
	///					GLUT_BITMAP_8_BY_13		
	///					GLUT_BITMAP_TIMES_ROMAN_10	
	///					GLUT_BITMAP_TIMES_ROMAN_24	
	///					GLUT_BITMAP_HELVETICA_10	
	///					GLUT_BITMAP_HELVETICA_12	
	///					GLUT_BITMAP_HELVETICA_18	
	///
	void fontSet(font);

	//--------------------------------------------------------------------------
	/// \brief	draws the specified text
	/// \param	text	-	the text string to draw
	/// \param	x		-	the x location of the text
	/// \param	y		-	the y location of the text
	/// \return	
	///
	void fontDraw(const char* text,int x,int y);

	//--------------------------------------------------------------------------
	/// \brief	returns the length (in pixels) of the text string
	/// \param	the string to check
	/// \return	the pixel length of the text string on the screen
	///
	unsigned int fontWidth(const char*);

	//--------------------------------------------------------------------------
	/// \brief	returns the height (in pixels) of the current font
	/// \return	the fonts height
	///
	unsigned int fontHeight();

#ifdef __cplusplus
}
#endif


#endif
