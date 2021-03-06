#include "core/XmlWalkmeshFile.h"

#include "core/EntityManager.h"
#include "core/Logger.h"
#include "core/Walkmesh.h"



XmlWalkmeshFile::XmlWalkmeshFile( const Ogre::String& file ):
    XmlFile( file )
{
}



XmlWalkmeshFile::~XmlWalkmeshFile()
{
}



void
XmlWalkmeshFile::Load()
{
    TiXmlNode* node = m_File.RootElement();
    Walkmesh* walkmesh = EntityManager::getSingleton().GetWalkmesh();

    if( node == nullptr || node->ValueStr() != "walkmesh" )
    {
        LOG_ERROR( "Field XML Manager: " + m_File.ValueStr() + " is not a valid walkmesh file! No <walkmesh> in root." );
        return;
    }

    node = node->FirstChild();
    while( node != nullptr )
    {
        if( node->Type() == TiXmlNode::TINYXML_ELEMENT && node->ValueStr() == "triangle" )
        {
            WalkmeshTriangle triangle;

            triangle.a = GetVector3( node, "a" );
            triangle.b = GetVector3( node, "b" );
            triangle.c = GetVector3( node, "c" );

            triangle.access_side[ 0 ] = GetInt( node, "a_b" );
            triangle.access_side[ 1 ] = GetInt( node, "b_c" );
            triangle.access_side[ 2 ] = GetInt( node, "c_a" );

            walkmesh->AddTriangle( triangle );
        }

        node = node->NextSibling();
    }
}
