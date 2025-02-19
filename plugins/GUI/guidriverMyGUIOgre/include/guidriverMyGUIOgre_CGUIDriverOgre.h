/*
 *  guidriverRocketOpenGL: module providing a GUI backend using Rocket and OpenGL
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GUCEF_MYGUIOGRE_CGUIDRIVEROGRE_H
#define GUCEF_MYGUIOGRE_CGUIDRIVEROGRE_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef __MYGUI_H__
#include "MyGUI.h"
#define __MYGUI_H__
#endif /* __MYGUI_H__ ? */

#ifndef __MYGUI_OGRE_RENDER_MANAGER_H__
#include "MyGUI_OgreRenderManager.h"
#define __MYGUI_OGRE_RENDER_MANAGER_H__
#endif /* __MYGUI_OGRE_RENDER_MANAGER_H__ ? */

#ifndef GUCEF_CORE_COBSERVINGNOTIFIER_H
#include "CObservingNotifier.h"
#define GUCEF_CORE_COBSERVINGNOTIFIER_H
#endif /* GUCEF_CORE_COBSERVINGNOTIFIER_H ? */

#ifndef GUCEF_CORE_CICONFIGURABLE_H
#include "CIConfigurable.h"
#define GUCEF_CORE_CICONFIGURABLE_H
#endif /* GUCEF_CORE_CICONFIGURABLE_H ? */

#ifndef GUCEF_GUIDRIVERMYGUI_CMYGUIDRIVER_H
#include "guidriverMyGUI_CMyGuiDriver.h"
#define GUCEF_GUIDRIVERMYGUI_CMYGUIDRIVER_H
#endif /* GUCEF_GUIDRIVERMYGUI_CMYGUIDRIVER_H ? */

#ifndef GUCEF_MYGUI_CDATAMANAGER_H
#include "guceMyGUI_CDataManager.h"
#define GUCEF_MYGUI_CDATAMANAGER_H
#endif /* GUCEF_MYGUI_CDATAMANAGER_H ? */

#ifndef GUCEF_MYGUI_CLOGADAPTER_H
#include "guidriverMyGUI_CLogAdapter.h"
#define GUCEF_MYGUI_CLOGADAPTER_H
#endif /* GUCEF_MYGUI_CLOGADAPTER_H ? */

#ifndef GUCEF_MYGUIOGRE_MACROS_H
#include "guidriverMyGUIOgre_macros.h"
#define GUCEF_MYGUIOGRE_MACROS_H
#endif /* GUCEF_MYGUIOGRE_MACROS_H ? */

#ifndef GUCEF_MYGUIOGRE_CIMAGELOADER_H
#include "guidriverMyGUIOgre_CImageLoader.h"
#define GUCEF_MYGUIOGRE_CIMAGELOADER_H
#endif /* GUCEF_MYGUIOGRE_CIMAGELOADER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace MYGUIOGRE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class GUCEF_MYGUIOGRE_EXPORT_CPP CGUIDriverOgre : public GUCEF::MYGUI::CMyGUIDriver
{
    public:

    CGUIDriverOgre( void );

    virtual ~CGUIDriverOgre();

    virtual GUI::TGuiContextPtr CreateGUIContext( GUI::TWindowContextPtr windowContext );

    virtual TGUIContextSet GetContextList( void );

    virtual GUI::UInt32 GetContextCount( void );

    virtual GUI::CString GetDriverName( void );

    virtual TStringSet GetAvailableFonts( void );

    virtual bool LoadFontFromAsset( const GUI::CString& assetPath );

    virtual const GUI::CString& GetClassTypeName( void ) const;

    virtual GUI::CString GetDriverProperty( const GUI::CString& propertyName ) const;

    /**
     *      Attempts to store the given tree in the file
     *      given according to the method of the codec metadata
     *
     *      @param tree the data tree you wish to store
     *      @return wheter storing the tree was successfull
     */
    virtual bool SaveConfig( CORE::CDataNode& tree ) const;

    /**
     *      Attempts to load data from the given file to the
     *      root node given. The root data will be replaced
     *      and any children the node may already have will be deleted.
     *
     *      @param treeroot pointer to the node that is to act as root of the data tree
     *      @return whether building the tree from the given file was successfull.
     */
    virtual bool LoadConfig( const CORE::CDataNode& treeroot );

    virtual MyGUI::Gui* GetMyGui( void );

    private:

    CGUIDriverOgre( const CGUIDriverOgre& src );

    private:

    GUI::CGUIDriver::TGUIContextSet m_contextSet;
    TStringSet m_fontTypes;
    MyGUI::Gui m_myGUI;
    MyGUI::OgreRenderManager m_renderManager;
    //CImageLoader m_imageLoader;
    MYGUI::CLogAdapter m_logAdapter;
    MYGUI::CDataManager m_dataManager;
    bool m_myGuiInitialized;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace MYGUIOGRE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_MYGUIOGRE_CGUIDRIVEROGRE_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 18-08-2010 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/
