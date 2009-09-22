/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef INITDATA_H
#define INITDATA_H

#include <eq/net/object.h>

namespace eqOsg {

	/// The init data holds all data which is needed during initalization.
	/// It is sent by the server to all render clients.
	/// It holds the frame data ID, so all clients can sync the frame data object.
	class InitData : public eq::net::Object
	{
	public:
		InitData();
		/// InitData deconstructor.
		~InitData();
		/// Sets the frame ID.
		/// @param id The id of the frame.
		void setFrameDataID( const uint32_t id );

		/// Returns the frame ID.
		/// @return The ID.
		uint32_t getFrameDataID() const;

		/// Parses the command line arguments and puts the things it can parse
		/// into the init data.
		/// @param argv The passed arguments.
		/// @param argc The passed arguments' counter.
		/// @return true if the command line was successfully parsed, false otherwise.
		bool parseCommandLine( char **argv, int argc );

		///Should an osg file model be loaded? This is usually set by InitData::parseCommandLine().
		///@param loadModel True/False
		void setLoadModel( bool loadModel ){_loadModel=loadModel;}
		
		///Should an osg file model be loaded? This is usually set by InitData::parseCommandLine().
		///@return True if a model will be loaded by the pipe.
		bool getLoadModel() const {return _loadModel;}

		///Sets the to load model file name.
		///@param fileName An existing osg model in the filesystem.
		void setModelFileName( const std::string& fileName ){_modelFileName=fileName;}

		///Returns the model filename.
		///@return The filename of the to load model.
		std::string getModelFileName()const {return _modelFileName;}
	protected:
		/// Passes the InitData's data to the stream.
		/// @param stream The Equalizer stream to write.
		virtual void getInstanceData( eq::net::DataOStream& stream );

		/// Gets the data out of the stream.
		/// @param stream The Equalizer stream to read.
		virtual void applyInstanceData( eq::net::DataIStream& stream );

	private:
		uint32_t _frameDataID;
		bool _loadModel;
		std::string _modelFileName;
	};
}
#endif
