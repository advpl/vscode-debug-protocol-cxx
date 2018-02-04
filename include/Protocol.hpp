#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include <string>
#include <vector>
#include "json.hpp"

namespace vscode_debug {
    //using boost::property_tree::ptree;
    using namespace std;
    using json = nlohmann::json;
    
    
	/** Base class of requests, responses, and events. */
	class ProtocolMessage {
		public :
            /** Sequence number. */
            int seq;
            /** Message type.
                Values: 'request', 'response', 'event', etc.
            */
            string type;
	};
    
    /** A client or server-initiated request. */
	class Request:  ProtocolMessage {
		// type: 'request';
		/** The command to execute. */
		public:
            string command ;
		/** Object containing arguments for the command. */
	    	//arguments?: any;
	};
	

/** Arguments for 'initialize' request. */
	struct InitializeRequestArguments {
		/** The ID of the (frontend) client using this adapter. */
		string clientID;
		/** The ID of the debug adapter. */
		string adapterID;
		/** The ISO-639 locale of the (frontend) client using this adapter, e.g. en-US or de-CH. */
		 string locale;
		/** If true all line numbers are 1-based (default). */
		bool linesStartAt1;
		/** If true all column numbers are 1-based (default). */
		bool columnsStartAt1;
		/** Determines in what format paths are specified. The default is 'path', which is the native format.
			Values: 'path', 'uri', etc.
		*/
		string pathFormat;
		/** Client supports the optional type attribute for variables. */
		bool supportsVariableType;
		/** Client supports the paging of variables. */
		bool supportsVariablePaging;
		/** Client supports the runInTerminal request. */
		bool supportsRunInTerminalRequest;
	};	
   
	class InitializeRequest : Request {
		// command: 'initialize';
		public:
		
		InitializeRequestArguments arguments;
	};
/*
	void to_json(json& j, const InitializeRequestArguments& p) {
        j = json{{"seq", p.seq}, {"type", p.type}};
    }
    void from_json(const json& j, InitializeRequestArguments& p) {
        p.seq = j.at("seq").get<int>();
        p.type = j.at("type").get<string>();

    }
*/

    //vector<string> ChecksumAlgorithm 
    //ChecksumAlgorithm = 'MD5' | 'SHA1' | 'SHA256' | 'timestamp';
    
	/** A ColumnDescriptor specifies what module attribute to show in a column of the ModulesView, how to format it, and what the column's label should be.
		It is only used if the underlying UI actually supports this level of customization.
	*/
	struct ColumnDescriptor {
		/** Name of the attribute rendered in this column. */
		string attributeName;
		/** Header UI label of column. */
		string label;
		/** Format to use for the rendered values in this column. TBD how the format strings looks like. */
		string format;
		/** Datatype of values in this column.  Defaults to 'string' if not specified. */
		string type;// : 'string' | 'number' | 'boolean' | 'unixTimestampUTC';
		/** Width of this column in characters (hint only). */
		int width;
	};


/** An ExceptionBreakpointsFilter is shown in the UI as an option for configuring how exceptions are dealt with. */
	struct ExceptionBreakpointsFilter {
		/** The internal ID of the filter. This value is passed to the setExceptionBreakpoints request. */
		string filter;
		/** The name of the filter. This will be shown in the UI. */
		string label;
		/** Initial value of the filter. If not specified a value 'false' is assumed. */
		bool _default;
	};

    /** Information about the capabilities of a debug adapter. */
    struct Capabilities {
		/** The debug adapter supports the configurationDoneRequest. */
		bool supportsConfigurationDoneRequest;
		/** The debug adapter supports function breakpoints. */
		bool supportsFunctionBreakpoints;
		/** The debug adapter supports conditional breakpoints. */
		bool supportsConditionalBreakpoints;
		/** The debug adapter supports breakpoints that break execution after a specified number of hits. */
		bool supportsHitConditionalBreakpoints;
		/** The debug adapter supports a (side effect free) evaluate request for data hovers. */
		bool supportsEvaluateForHovers;
		/** Available filters or options for the setExceptionBreakpoints request. */
		vector<ExceptionBreakpointsFilter> exceptionBreakpointFilters;
		/** The debug adapter supports stepping back via the stepBack and reverseContinue requests. */
		bool supportsStepBack;
		/** The debug adapter supports setting a variable to a value. */
		bool supportsSetVariable;
		/** The debug adapter supports restarting a frame. */
		bool supportsRestartFrame;
		/** The debug adapter supports the gotoTargetsRequest. */
		bool supportsGotoTargetsRequest;
		/** The debug adapter supports the stepInTargetsRequest. */
		bool supportsStepInTargetsRequest;
		/** The debug adapter supports the completionsRequest. */
		bool supportsCompletionsRequest;
		/** The debug adapter supports the modules request. */
		bool supportsModulesRequest;
		/** The set of additional module information exposed by the debug adapter. */
		vector <ColumnDescriptor> additionalModuleColumns;
		/** Checksum algorithms supported by the debug adapter. */
		//supportedChecksumAlgorithms?: ChecksumAlgorithm[];
		/** The debug adapter supports the RestartRequest. In this case a client should not implement 'restart' by terminating and relaunching the adapter but by calling the RestartRequest. */
		bool supportsRestartRequest;
		/** The debug adapter supports 'exceptionOptions' on the setExceptionBreakpoints request. */
		bool supportsExceptionOptions;
		/** The debug adapter supports a 'format' attribute on the stackTraceRequest, variablesRequest, and evaluateRequest. */
		bool supportsValueFormattingOptions;
		/** The debug adapter supports the exceptionInfo request. */
		bool supportsExceptionInfoRequest;
		/** The debug adapter supports the 'terminateDebuggee' attribute on the 'disconnect' request. */
		bool supportTerminateDebuggee;
		/** The debug adapter supports the delayed loading of parts of the stack, which requires that both the 'startFrame' and 'levels' arguments and the 'totalFrames' result of the 'StackTrace' request are supported. */
		bool supportsDelayedStackTraceLoading;
		/** The debug adapter supports the 'loadedSources' request. */
		bool supportsLoadedSourcesRequest;
	};
    void from_json(const json& j, ProtocolMessage& p);
	void from_json(const json& j, Request& p);	
	void from_json(const json& j, InitializeRequest& p);
}

    

#endif