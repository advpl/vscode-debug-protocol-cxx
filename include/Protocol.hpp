#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include <string>
#include <vector>
#include "json.hpp"
/**
 * https://github.com/Microsoft/vscode-debugadapter-node/tree/master/protocol
 * 
 * 
*/
//Protocol Version 1.26
namespace vscode_debug {
    //using boost::property_tree::ptree;
    using namespace std;
    using json = nlohmann::json;	
    
	/** Base class of requests, responses, and events. */
	class ProtocolMessage {
		public:
            /** Sequence number. */
            int seq;
            /** Message type.
                Values: 'request', 'response', 'event', etc.
            */
            string type;
			ProtocolMessage(){};
			ProtocolMessage(string ptype,int pseq):type(ptype),seq(pseq)
			{};
			ProtocolMessage(string ptype):type(ptype){};
	};
    
    /** A client or server-initiated request. */
	class Request: public ProtocolMessage {
		// type: 'request';
		/** The command to execute. */
		public:
            string command ;
		/** Object containing arguments for the command. */
	    	//arguments?: any;
	};
	class ResponseBody{

	};

/** Response to a request. */
	class Response: public ProtocolMessage {
		public:
			// type: 'response';
			/** Sequence number of the corresponding request. */
			int request_seq;
			/** Outcome of the request. */
			bool success;
			/** The command requested. */
			string command;
			/** Contains error message if success == false. */
			string message;
			/** Contains request result if success is true and optional error details if success is false. */
			ResponseBody body;
			Response(Request &req) :ProtocolMessage("response",req.seq)
			{
				success = true;
				request_seq = req.seq;
				command = req.command;

			}
			void SetErrorBody(string msg, ResponseBody bdy ) {
				success = false;
				message = msg;
				body = bdy;
			}
	};
	/** Server-initiated event. */	
	class Event: public ProtocolMessage {
		public:
			Event(string et) :ProtocolMessage("event"){
				event= et;
			}
			string event;
	};


/** Event message for 'initialized' event type.
		This event indicates that the debug adapter is ready to accept configuration requests (e.g. SetBreakpointsRequest, SetExceptionBreakpointsRequest).
		A debug adapter is expected to send this event when it is ready to accept configuration requests (but not before the InitializeRequest has finished).
		The sequence of events/requests is as follows:
		- adapters sends InitializedEvent (after the InitializeRequest has returned)
		- frontend sends zero or more SetBreakpointsRequest
		- frontend sends one SetFunctionBreakpointsRequest
		- frontend sends a SetExceptionBreakpointsRequest if one or more exceptionBreakpointFilters have been defined (or if supportsConfigurationDoneRequest is not defined or false)
		- frontend sends other future configuration requests
		- frontend sends one ConfigurationDoneRequest to indicate the end of the configuration
	*/
	class InitializedEvent : public Event
	{
		public:
			InitializedEvent():Event("initialized"){

			}
	};

	/** Event message for 'terminated' event types.
		The event indicates that debugging of the debuggee has terminated.
	*/
	 class TerminatedEvent : public Event
	{
		public:
			TerminatedEvent(): Event("terminated"){

			}
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
		InitializeRequestArguments() : linesStartAt1(),columnsStartAt1(),supportsVariableType(),supportsVariablePaging(),supportsRunInTerminalRequest()
		{

		}
	};	
   
	class InitializeRequest : public Request {
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

/** The checksum of an item calculated by the specified algorithm. */
	struct Checksum {
		/** The algorithm used to calculate this checksum. */
		string algorithm; //: ChecksumAlgorithm;
		/** Value of the checksum. */
		string checksum;
	};

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
		Capabilities():supportsConfigurationDoneRequest(),supportsFunctionBreakpoints(),supportsConditionalBreakpoints(),supportsHitConditionalBreakpoints(),supportsEvaluateForHovers(),supportsStepBack(),supportsSetVariable(),
		supportsRestartFrame(),supportsGotoTargetsRequest(),supportsStepInTargetsRequest(),supportsCompletionsRequest(),supportsModulesRequest(),supportsRestartRequest(),supportsExceptionOptions(),
		supportsValueFormattingOptions(),supportsExceptionInfoRequest(),supportTerminateDebuggee(),supportsDelayedStackTraceLoading(),supportsLoadedSourcesRequest()
		{

		}
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
		vector <string> supportedChecksumAlgorithms; //?: ChecksumAlgorithm[];
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

	/** Arguments for 'launch' request. */
	struct LaunchRequestArguments {
		/** If noDebug is true the launch request should launch the program without enabling debugging. */
		bool noDebug;
	};
	/** Launch request; value of command field is 'launch'. */
	class LaunchRequest : Request {
		// command: 'launch';
		public:
		LaunchRequestArguments arguments;	

	};

	/** Response to 'initialize' request. */
	class InitializeResponse: public Response {
		/** The capabilities of this debug adapter. */
		public:
			Capabilities body;
			InitializeResponse(InitializeRequest &initreq) : Response((Request&) initreq)
			{}
	};

/** A structured message object. Used to return errors from requests. */
	struct Message {
		/** Unique identifier for the message. */
		int id;//: number;
		/** A format string for the message. Embedded variables have the form '{name}'.
			If variable name starts with an underscore character, the variable does not contain user data (PII) and can be safely used for telemetry purposes.
		*/
		string format ;
		/** An object used as a dictionary for looking up the variables in the format string. */
		vector<string> variables;//variables?: { [key: string]: string; };
		/** If true send to telemetry. */
		bool sendTelemetry;//?: boolean;
		/** If true show user. */
		bool showUser;//?: boolean;
		/** An optional url where additional information about this message can be found. */
		string url;//?: string;
		/** An optional label that is presented to the user as the UI for opening the url. */
		string urlLabel;//?: string;
		public:
			Message(){};
		 	Message(int id, string format):id(id),format(format),showUser(true),sendTelemetry(false) {
				 
				 }
				 
			Message(int id, string format, vector<string>arguments,bool user, bool telemetry):id(id),format(format),showUser(user),sendTelemetry(telemetry) {
			
			}
	};
		class ErrorResponseBody : public ResponseBody {
		public:
			Message error;
			ErrorResponseBody(Message error):error(error) {			
		}
	};

	/** A Source is a descriptor for source code. It is returned from the debug adapter as part of a StackFrame and it is used by clients when specifying breakpoints. */
	struct Source {
		/** The short name of the source. Every source returned from the debug adapter has a name. When sending a source to the debug adapter this name is optional. */
		string name;
		/** The path of the source to be shown in the UI. It is only used to locate and load the content of the source if no sourceReference is specified (or its vaule is 0). */
		string path;
		/** If sourceReference > 0 the contents of the source must be retrieved through the SourceRequest (even if a path is specified). A sourceReference is only valid for a session, so it must not be used to persist a source. */
		int sourceReference;
		/** An optional hint for how to present the source in the UI. A value of 'deemphasize' can be used to indicate that the source is not available or that it is skipped on stepping. */
		string presentationHint; // ?: 'normal' | 'emphasize' | 'deemphasize';
		/** The (optional) origin of this source: possible values 'internal module', 'inlined content from source map', etc. */
		string origin;
		/** An optional list of sources that are related to this source. These may be the source that generated this source. */
		vector<Source> sources;
		/** Optional data that a debug adapter might want to loop through the client. The client should leave the data intact and persist it across sessions. The client should not interpret the data. */
		string adapterData; //?: any;
		/** The checksums associated with this file. */
		vector<Checksum> checksums;
	};


	/** Information about a Breakpoint created in setBreakpoints or setFunctionBreakpoints. */
	struct Breakpoint {
		/** An optional unique identifier for the breakpoint. */
		int id;
		/** If true breakpoint could be set (but not necessarily at the desired location). */
		bool verified;
		/** An optional message about the state of the breakpoint. This is shown to the user and can be used to explain why a breakpoint could not be verified. */
		string message;
		/** The source where the breakpoint is located. */
		Source source;
		/** The start line of the actual range covered by the breakpoint. */
		int line;
		/** An optional start column of the actual range covered by the breakpoint. */
		int column;
		/** An optional end line of the actual range covered by the breakpoint. */
		int endLine;
		/** An optional end column of the actual range covered by the breakpoint. If no end line is given, then the end column is assumed to be in the start line. */
		int endColumn;
	};

	/** Event message for 'breakpoint' event type.
		The event indicates that some information about a breakpoint has changed.
	*/
	class BreakpointEvent: public Event {
		public:
			BreakpointEvent():Event("breakpoint"){				
			}
			/** The reason for the event.
				Values: 'changed', 'new', 'removed', etc.
			*/
			string reason;
			/** The breakpoint. */
			Breakpoint breakpoint;
	};	
		/** Properties of a breakpoint or logpoint passed to the setBreakpoints request. */
	struct SourceBreakpoint {
		/** The source line of the breakpoint or logpoint. */
		int line;
		/** An optional source column of the breakpoint. */
		int column;
		/** An optional expression for conditional breakpoints. */
		string condition;
		/** An optional expression that controls how many hits of the breakpoint are ignored. The backend is expected to interpret the expression as needed. */
		string hitCondition;
		/** If this attribute exists and is non-empty, the backend must not 'break' (stop) but log the message instead. Expressions within {} are interpolated. */
		string logMessage;
	};
	/** Arguments for 'setBreakpoints' request. */
	struct SetBreakpointsArguments {
		/** The source location of the breakpoints; either source.path or source.reference must be specified. */
		Source source;
		/** The code locations of the breakpoints. */
		vector<SourceBreakpoint>breakpoints;
		/** Deprecated: The code locations of the breakpoints. */
		vector<int> lines;
		/** A value of true indicates that the underlying source has been modified which results in new breakpoint locations. */
		bool sourceModified;
	};

	/** SetBreakpoints request; value of command field is 'setBreakpoints'.
		Sets multiple breakpoints for a single source and clears all previous breakpoints in that source.
		To clear all breakpoint for a source, specify an empty array.
		When a breakpoint is hit, a StoppedEvent (event type 'breakpoint') is generated.
	*/
	class SetBreakpointsRequest: public Request {
		// command: 'setBreakpoints';
		public:
			SetBreakpointsArguments arguments;
	};

	/** Response to 'setBreakpoints' request.
		Returned is information about each breakpoint created by this request.
		This includes the actual code location and whether the breakpoint could be verified.
		The breakpoints returned are in the same order as the elements of the 'breakpoints'
		(or the deprecated 'lines') in the SetBreakpointsArguments.
	*/
	class SetBreakpointsResponse: public Response {
		/** The capabilities of this debug adapter. */
		public:
			//Capabilities body;
			vector<Breakpoint> breakpoints;
			SetBreakpointsResponse(SetBreakpointsResponse &initreq) : Response((Request&) initreq)
			{}
	};	

	void from_json(const json& j, SetBreakpointsRequest& p);
	void from_json(const json& j, SourceBreakpoint& p);
	void from_json(const json& j, SetBreakpointsArguments& p);
	void from_json(const json& j, Checksum& p);
    void from_json(const json& j, Source& p);
	void from_json(const json& j, ProtocolMessage& p);
	void from_json(const json& j, Request& p);	
	void from_json(const json& j, InitializeRequest& p);
	void from_json(const json& j, LaunchRequest& p);
	void from_json(const json& j, LaunchRequestArguments& p);
	
	void to_json(json& j, const Capabilities& p);
	void to_json(json& j, const Response& p);
	void to_json(json& j, const InitializeResponse& p);
	void to_json(json& j, const ProtocolMessage& p);
	void to_json(json& j, const Event& p);
	void to_json(json& j, const TerminatedEvent& p); 
	void to_json(json& j, const InitializedEvent& p);
	
}

    

#endif