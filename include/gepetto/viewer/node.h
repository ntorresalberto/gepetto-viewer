//
//  node.h
//  gepetto-viewer
//
//  Created by Justin Carpentier, Mathieu Geisert in November 2014.
//  Copyright (c) 2014 LAAS-CNRS. All rights reserved.
//

#ifndef SCENEVIEWER_NODE_HH
#define SCENEVIEWER_NODE_HH

#include <iostream>
#include <gepetto/viewer/config-osg.h>

namespace graphics {
    class NodeVisitor;
    
    DEF_CLASS_SMART_PTR(Node)
    
    class Node
    {
    private:
        static bool firstTime_;
        static osg::NodeRefPtr arrow_;
        static osg::NodeRefPtr circle_;

        std::string id_name_; // automoatic id generated by the program

        /** PositionAttitudeTransform related to the global configuration */
        osg::AutoTransformRefPtr auto_transform_ptr_;
        osg::AutoTransformRefPtr static_auto_transform_ptr_;

        /** Position of the arrows */
        osg::PositionAttitudeTransformRefPtr arrows_transform_ptr_;
        
        /** Associated wireframe node */
        osg::PolygonModeRefPtr polygon_mode_ptr_;
        osg::GroupRefPtr wireframe_node_ptr_;
        osg::GroupRefPtr normal_node_ptr_;
        
        /** Associated switch node */
        /** TODO: The use of multiswitch may be better */
        osg::SwitchRefPtr switch_node_ptr_;
        osg::SwitchRefPtr hl_switch_node_ptr_;
        
        /** Initialization function */
        void init ();

        ::osg::Group* setupHighlightState (unsigned int state);

    protected:
        /** protected because it's used in LeafNodeCapsule */
        ::osg::GeodeRefPtr landmark_geode_ptr_;

        /** Geode pointer for landmarks */
	::osg::GeodeRefPtr geode_ptr_;
        /** Alpha value */
        float alpha_;

        /**
         \brief Default constructor
         */
        Node (const std::string& name);
        
        /** Copy constructor */
        Node (const Node& other);
        
        /**
         \brief Return the root node to include it in the scene
         */
        ::osg::GroupRefPtr asQueue () const
        {
            return static_auto_transform_ptr_;
        }
        
        void setID (const std::string& id_name)
        {
            id_name_ = id_name;
            switch_node_ptr_->setName (id_name_);
        }
    public:
        enum Arrow {
          NONE    = 0,
          ROT_X   = 1,
          ROT_Y   = 2,
          ROT_Z   = 4,
          TRANS_X = 8,
          TRANS_Y = 16,
          TRANS_Z = 32,
          ALL     = 63
        };

        /**
         \brief returns rotation and position of the node
         in word frame
         */
        std::pair<osgVector3, osgQuat> getGlobalTransform() const;

        /**
         \brief getID is a public method for getting the id_name of the Object
         */
        std::string getID () const
        {
            return id_name_;
        }
        
        /** Apply a new global configuration
         */
        void applyConfiguration (const osgVector3 & position, const osgQuat & quat);
        
	/** Set Static transformation
         */
        void setStaticTransform (const osgVector3 & position, const osgQuat & quat);
        
	/** Get Static rotation
        */
        osgQuat getStaticRotation() const;

	/** Get Static position
        */
        osgVector3 getStaticPosition() const;

        /**
         \brief Virtual method for setting the visibility mode of the object : visible or not visible
         \param visibilitymode state
         */
        virtual void setVisibilityMode (const VisibilityMode& visibility_state);
        
        /**
         \brief Virtual method for setting the lighting mode of the object : influence by light or not
         \param lightingmode state
         */
        virtual void setLightingMode (const LightingMode& lighting_state);
        
        /**
         \brief Virtual method for setting the wireframe mode of the object : visible or not
         \param wireframemode state
         */
        virtual void setWireFrameMode (const WireFrameMode& wireframe_state);
        
        /** Set scale value of the OSG object */
        virtual void setScale (float scale);

        /** Set scales value of the OSG object */
        virtual void setScale (const osg::Vec3d & scale);

        /** Set the color of the object */
        virtual void setColor (const osgVector4& color) = 0;

        /** Select the arrows to be shown around the selected body */
        virtual void selectArrows (
            int arrows = ROT_X | ROT_Y | ROT_Z | TRANS_X | TRANS_Y | TRANS_Z);

        virtual void setArrowsVisibility (const VisibilityMode& visibility);
        
        /**
         \brief Return the root node to include it in the scene
         */
        virtual ::osg::GroupRefPtr asGroup () const
        {
            return switch_node_ptr_;
        }

        virtual void addLandmark(const float &size);

        ::osg::StateSetRefPtr getOrCreateRootStateSet ()
        {
          return switch_node_ptr_->getOrCreateStateSet ();
        }

        void deleteLandmark();

        void setHighlightState (unsigned int state);
        
        /*Tools::ConfigurationPtr_t getConfiguration () const
        {
            Tools::ConfigurationPtr_t configuration = Tools::Configuration::create(toDefVector3(auto_transform_ptr_->getPosition()),toEigenQuat(auto_transform_ptr_->getRotation()));
            return configuration;
        }*/

        virtual void setAlpha (const float& alpha);
	float getAlpha() const;

        virtual void accept (NodeVisitor& visitor);
        virtual void traverse (NodeVisitor& visitor);

        /* Destructor */
        virtual ~Node ();
        
    }; /* class Node */
    
} /* namespace graphics */

#endif /* dSCENEVIEWER_NODE_HH */
