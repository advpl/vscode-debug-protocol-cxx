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
	struct StoppedEventBody
	{
		/** The reason for the event.
				For backward compatibility this string is shown in the UI if the 'description' attribute is missing (but it must not be translated).
				Values: 'step', 'breakpoint', 'exception', 'pause', 'entry', etc.
			*/
			string reason;
			/** The full reason for the event, e.g. 'Paused on exception'. This string is shown in the UI as is. */
			string description; //op
			/** The thread which was stopped. */
			int threadId;//op
			/** Additional information. E.g. if reason is 'exception', text contains the exception name. This string is shown in the UI. */
			string text;
			/** If allThreadsStopped is true, a debug adapter can announce that all threads have stopped.
				*  The client should use this information to enable that all threads can be expanded to access their stacktraces.
				*  If the attribute is missing or false, only the thread with the given threadId can be expanded.
			*/
			bool allThreadsStopped;//op
	};

	/** Event message for 'stopped' event type.
		The event indicates that the execution of the debuggee has stopped due to some condition.
		This can be caused by a break point previously set, a stepping action has completed, by executing a debugger statement etc.
	*/
	class StoppedEvent : public Event {
			public:
				StoppedEventBody body;
				StoppedEvent():Event("stopped"){
				
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
	/** Arguments for 'configurationDone' request.
		The configurationDone request has no standardized attributes.
	*/
	class ConfigurationDoneArguments {
	};

/** A Thread */
	struct Thread {
		/** Unique identifier for the thread. */
		int id;
		/** A name of the thread. */
		string name;
	};

/** Thread request; value of command field is 'threads'.
		The request retrieves a list of all threads.
	*/
	class ThreadsRequest : public Request {
	
		// command: 'threads';
	};
	struct ThreadsResponseBody
	{
		vector<Thread> threads;
	};
	/** Response to 'threads' request. */
	class ThreadsResponse :public Response {
		public:
			/** All threads. */
			ThreadsResponseBody body;
			ThreadsResponse(ThreadsRequest &initreq) : Response((Request&) initreq)
			{}
		
	};























	/** ConfigurationDone request; value of command field is 'configurationDone'.
		The client of the debug protocol must send this request at the end of the sequence of configuration requests (which was started by the InitializedEvent).
	*/
	class ConfigurationDoneRequest : public Request {
		// command: 'configurationDone';
		public:		
			ConfigurationDoneArguments arguments;		
	};
	/** Arguments for 'continue' request. */
	struct ContinueArguments {
		/** Continue execution for the specified thread (if possible). If the backend cannot continue on a single thread but will continue on all threads, it should set the allThreadsContinued attribute in the response to true. */
		int threadId;
	};

/** Continue request; value of command field is 'continue'.
		The request starts the debuggee to run again.
	*/
	class ContinueRequest : public Request {	
		// command: 'continue';
		public:
			ContinueArguments arguments;
	};

	struct ContinueResponseBody
	{
		bool allThreadsContinued;
	};
	/** Response to 'continue' request. */
	class ContinueResponse: public Response {	
		
			public:
			/** If true, the continue request has ignored the specified thread and continued all threads instead. If this attribute is missing a value of 'true' is assumed for backward compatibility. */
				ContinueResponseBody body;
				
			ContinueResponse(ContinueRequest &initreq) : Response((Request&) initreq)
			{}
	};
	
	/** Arguments for 'next' request. */
	struct NextArguments {
		/** Execute 'next' for this thread. */
		int threadId;//: number;
	};
	/** Next request; value of command field is 'next'.
		The request starts the debuggee to run again for one step.
		The debug adapter first sends the NextResponse and then a StoppedEvent (event type 'step') after the step has completed.
	*/
	class NextRequest  : public Request {	
		// command: 'next';
		public:
			NextArguments arguments;
	};

	

	/** Response to 'next' request. This is just an acknowledgement, so no body field is required. */
	class NextResponse : public Response {
		public:			
				
			NextResponse (NextRequest &initreq) : Response((Request&) initreq)
			{}
	};

/** Arguments for 'stepIn' request. */
	struct StepInArguments {
		/** Execute 'stepIn' for this thread. */
		int threadId;//: number;
		/** Optional id of the target to step into. */
		int targetId;//?: number;
	};

/** StepIn request; value of command field is 'stepIn'.
		The request starts the debuggee to step into a function/method if possible.
		If it cannot step into a target, 'stepIn' behaves like 'next'.
		The debug adapter first sends the StepInResponse and then a StoppedEvent (event type 'step') after the step has completed.
		If there are multiple function/method calls (or other targets) on the source line,
		the optional argument 'targetId' can be used to control into which target the 'stepIn' should occur.
		The list of possible targets for a given source line can be retrieved via the 'stepInTargets' request.
	*/
	
	class StepInRequest : public Request {
		public:
		// command: 'stepIn';
			StepInArguments arguments;//: StepInArguments;
	};

	

	/** Response to 'stepIn' request. This is just an acknowledgement, so no body field is required. */
	class StepInResponse : public Response {
		public:
			StepInResponse (StepInRequest &initreq) : Response((Request&) initreq)
			{}
	};

	

















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
		Source(){}
		Source(string name,string path):name(name),path(path),sourceReference(0){}
	};


	/** A Stackframe contains the source location. */
	struct StackFrame {
		/** An identifier for the stack frame. It must be unique across all threads. This id can be used to retrieve the scopes of the frame with the 'scopesRequest' or to restart the execution of a stackframe. */
		int id;//: number;
		/** The name of the stack frame, typically a method name. */
		string name;//: string;
		/** The optional source of the frame. */
		Source source;//?: Source;
		/** The line within the file of the frame. If source is null or doesn't exist, line is 0 and must be ignored. */
		int line;//: number;
		/** The column within the line. If source is null or doesn't exist, column is 0 and must be ignored. */
		int column;//: number;
		/** An optional end line of the range covered by the stack frame. */
		int endLine;//?: number;
		/** An optional end column of the range covered by the stack frame. */
		int endColumn;//?: number;
		/** The module associated with this frame, if any. */
		string moduleId;//?: number | string;
		/** An optional hint for how to present this frame in the UI. A value of 'label' can be used to indicate that the frame is an artificial frame that is used as a visual label or separator. A value of 'subtle' can be used to change the appearance of a frame in a 'subtle' way. */
		string presentationHint;//?: 'normal' | 'label' | 'subtle';
		StackFrame()
		{
			endLine = -1;
			endColumn = -1;
		}
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
		Breakpoint(){
			id = -1;
			line = -1;
			column = -1;
			endLine = -1;
			endColumn =-1;
		}
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
	class SetBreakpointsResponseBody : public ResponseBody{
		public:
			vector<Breakpoint> breakpoints;
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
			SetBreakpointsResponseBody body;
			SetBreakpointsResponse(SetBreakpointsRequest &initreq) : Response((Request&) initreq)
			{}
	};	
	class ValueFormat
	{
		public:
			bool hex;
			ValueFormat(){}
	};
	

	/** Provides formatting information for a stack frame. */
	class StackFrameFormat : public ValueFormat {
		public:
			/** Displays parameters for the stack frame. */
			bool parameters;//?: boolean;
			/** Displays the types of parameters for the stack frame. */
			bool parameterTypes;//?: boolean;
			/** Displays the names of parameters for the stack frame. */
			bool parameterNames;//?: boolean;
			/** Displays the values of parameters for the stack frame. */
			bool parameterValues;//?: boolean;
			/** Displays the line number of the stack frame. */
			bool line;//?: boolean;
			/** Displays the module of the stack frame. */
			bool module;//?: boolean;
			/** Includes all stack frames, including those the debug adapter might otherwise hide. */
			bool includeAll;//?: boolean;
			StackFrameFormat(){}
	};
	

/** Arguments for 'stackTrace' request. */
	struct StackTraceArguments {
		/** Retrieve the stacktrace for this thread. */
		int threadId;
		/** The index of the first frame to return; if omitted frames start at 0. */
		int startFrame;//op
		/** The maximum number of frames to return. If levels is not specified or 0, all frames are returned. */
		int levels;//op
		/** Specifies details on how to format the stack frames. */
		StackFrameFormat format;//?: ;
	};
	


/** StackTrace request; value of command field is 'stackTrace'. The request returns a stacktrace from the current execution state. */
	class StackTraceRequest : public Request {
		public:
		// command: 'stackTrace';
			StackTraceArguments arguments;
	};

	struct StackTraceResponseBody
	{
		/** The frames of the stackframe. If the array has length zero, there are no stackframes available.
			This means that there is no location information available.
		*/
		vector<StackFrame> stackFrames;
		/** The total number of frames available. */
		int totalFrames;
	};

	/** Response to 'stackTrace' request. */
	class StackTraceResponse :public Response {
		public:
			StackTraceResponseBody body;
			StackTraceResponse(StackTraceRequest &initreq) : Response((Request&) initreq)
			{}
		
	};
	
	
	/** Optional properties of a variable that can be used to determine how to render the variable in the UI. */
	struct VariablePresentationHint {
		/** The kind of variable. Before introducing additional values, try to use the listed values.
			Values: 
			'property': Indicates that the object is a property.
			'method': Indicates that the object is a method.
			'class': Indicates that the object is a class.
			'data': Indicates that the object is data.
			'event': Indicates that the object is an event.
			'baseClass': Indicates that the object is a base class.
			'innerClass': Indicates that the object is an inner class.
			'interface': Indicates that the object is an interface.
			'mostDerivedClass': Indicates that the object is the most derived class.
			'virtual': Indicates that the object is virtual, that means it is a synthetic object introduced by the adapter for rendering purposes, e.g. an index range for large arrays.
			etc.
		*/
		string kind;//: string;
		/** Set of attributes represented as an array of strings. Before introducing additional values, try to use the listed values.
			Values: 
			'static': Indicates that the object is static.
			'constant': Indicates that the object is a constant.
			'readOnly': Indicates that the object is read only.
			'rawString': Indicates that the object is a raw string.
			'hasObjectId': Indicates that the object can have an Object ID created for it.
			'canHaveObjectId': Indicates that the object has an Object ID associated with it.
			'hasSideEffects': Indicates that the evaluation had side effects.
			etc.
		*/
		vector<string> attributes;//?: string[];
		/** Visibility of variable. Before introducing additional values, try to use the listed values.
			Values: 'public', 'private', 'protected', 'internal', 'final', etc.
		*/
		string visibility;//?: string;
	};


	/** A Variable is a name/value pair.
		Optionally a variable can have a 'type' that is shown if space permits or when hovering over the variable's name.
		An optional 'kind' is used to render additional properties of the variable, e.g. different icons can be used to indicate that a variable is public or private.
		If the value is structured (has children), a handle is provided to retrieve the children with the VariablesRequest.
		If the number of named or indexed children is large, the numbers should be returned via the optional 'namedVariables' and 'indexedVariables' attributes.
		The client can use this optional information to present the children in a paged UI and fetch them in chunks.
	*/
	class Variable {
		public:
			/** The variable's name. */
			string name;
			/** The variable's value. This can be a multi-line text, e.g. for a function the body of a function. */
			string value;
			/** The type of the variable's value. Typically shown in the UI when hovering over the value. */
			string type;
			/** Properties of a variable that can be used to determine how to render the variable in the UI. */
			VariablePresentationHint presentationHint;//?
			/** Optional evaluatable name of this variable which can be passed to the 'EvaluateRequest' to fetch the variable's value. */
			string evaluateName;//?: string;
			/** If variablesReference is > 0, the variable is structured and its children can be retrieved by passing variablesReference to the VariablesRequest. */
			int variablesReference;//: number;
			/** The number of named child variables.
				The client can use this optional information to present the children in a paged UI and fetch them in chunks.
			*/
			int namedVariables;//?: number;
			/** The number of indexed child variables.
				The client can use this optional information to present the children in a paged UI and fetch them in chunks.
			*/
			int indexedVariables; //?: number;
			Variable():variablesReference(0),namedVariables(0),indexedVariables(0){}
			Variable(string name, string value, int variablesReference):name(name),value(value),variablesReference(variablesReference){}
	};
	



/** A Scope is a named container for variables. Optionally a scope can map to a source or a range within a source. */
	struct Scope {
		/** Name of the scope such as 'Arguments', 'Locals'. */
		string name;//: string;
		/** The variables of this scope can be retrieved by passing the value of variablesReference to the VariablesRequest. */
		int variablesReference;//: number;
		/** The number of named variables in this scope.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int namedVariables;//?: number;
		/** The number of indexed variables in this scope.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int indexedVariables;//?: number;
		/** If true, the number of variables in this scope is large or expensive to retrieve. */
		bool expensive;//: boolean;
		/** Optional source for this scope. */
		Source source;//?: Source;
		/** Optional start line of the range covered by this scope. */
		int line;//?: number;
		/** Optional start column of the range covered by this scope. */
		int column;//?: number;
		/** Optional end line of the range covered by this scope. */
		int endLine;//?: number;
		/** Optional end column of the range covered by this scope. */
		int endColumn;//?: number;
		Scope(string pname, int pvariablesReference):Scope()
		{
			name = pname;
			variablesReference = pvariablesReference;
			expensive = false;
		}
		Scope()
		{	
			line = -1;
			column = -1;
			endLine = -1;
			endColumn = -1;
			indexedVariables = -1;
			namedVariables = -1;
		}
	};


    
	/** Arguments for 'scopes' request. */
	struct ScopesArguments {
		/** Retrieve the scopes for this stackframe. */
		int frameId;//: number;
	};

	/** Scopes request; value of command field is 'scopes'.
		The request returns the variable scopes for a given stackframe ID.
	*/
	class ScopesRequest : public Request {
		// command: 'scopes';
		public:
			ScopesArguments arguments;//: ScopesArguments;
	};

	struct ScopesResponseBody
	{
		vector<Scope> scopes;
	};

	/** Response to 'scopes' request. */
	class ScopesResponse :public Response {
		public:
			ScopesResponseBody body;
			ScopesResponse (ScopesRequest &initreq) : Response((Request&) initreq)
			{}
	};
	
	



	/** Arguments for 'variables' request. */
	struct VariablesArguments {
		/** The Variable reference. */
		int variablesReference;//: number;
		/** Optional filter to limit the child variables to either named or indexed. If ommited, both types are fetched. */
		string filter;//?: 'indexed' | 'named';
		/** The index of the first variable to return; if omitted children start at 0. */
		int start;//?: number;
		/** The number of variables to return. If count is missing or 0, all variables are returned. */
		int count;//?: number;
		/** Specifies details on how to format the Variable values. */
		ValueFormat format;//?: ValueFormat;
	};
	


	/** Variables request; value of command field is 'variables'.
		Retrieves all child variables for the given variable reference.
		An optional filter can be used to limit the fetched children to either named or indexed children.
	*/
	class VariablesRequest : public Request {	
		// command: 'variables';
		public:
			VariablesArguments arguments;
	};

	struct VariablesResponseBody
	{
		vector<Variable> variables;
	};
	
	/** Response to 'variables' request. */
	class VariablesResponse: public Response {	
		
			public:
			/** All (or a range) of variables for the given variable reference. */
				VariablesResponseBody body;
				
			VariablesResponse(VariablesRequest &initreq) : Response((Request&) initreq)
			{}
	};

	struct SetVariableResponseBody
	{
		/** The new value of the variable. */
		string value;//: string;
		/** The type of the new value. Typically shown in the UI when hovering over the value. */
		string type;//?: string;
		/** If variablesReference is > 0, the new value is structured and its children can be retrieved by passing variablesReference to the VariablesRequest. */
		int variablesReference;//?: number;
		/** The number of named child variables.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int namedVariables;//?: number;
		/** The number of indexed child variables.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int indexedVariables;//?: number;
		
		SetVariableResponseBody()
		{
			variablesReference = -1;
			namedVariables = -1;
			indexedVariables = -1;
		}

	};
/** Response to 'setVariable' request. */
	class SetVariableResponse : public Response {
		SetVariableResponseBody body;		
		 SetVariableResponse(VariablesRequest &initreq) : Response((Request&) initreq)
		{}
	};

	void to_json(json& j, const VariablesResponseBody& p);
	void to_json(json& j, const VariablesResponse& p);
  	
	void to_json(json& j, const SetVariableResponseBody& p);
	void from_json(const json& j, VariablesArguments& p);
	void from_json(const json& j, VariablesRequest& p);


	void from_json(const json& j, ScopesRequest& p);
    void from_json(const json& j, ScopesArguments& p);

	void to_json(json& j, const VariablePresentationHint& p);
	void to_json(json& j, const Variable& p);
	void from_json(const json& j, SetBreakpointsRequest& p);
	void from_json(const json& j, SourceBreakpoint& p);
	void from_json(const json& j, SetBreakpointsArguments& p);
	void from_json(const json& j, Checksum& p);
	void to_json(json& j, const Checksum& p);
    void from_json(const json& j, Source& p);
	void from_json(const json& j, ProtocolMessage& p);
	void from_json(const json& j, Request& p);	
	void from_json(const json& j, InitializeRequest& p);
	void from_json(const json& j, ConfigurationDoneRequest& p);
	void from_json(const json& j, ConfigurationDoneArguments& p);

	
	void from_json(const json& j, LaunchRequest& p);
	void from_json(const json& j, LaunchRequestArguments& p);
	
	void to_json(json& j, const Capabilities& p);
	void to_json(json& j, const Response& p);
	void to_json(json& j, const InitializeResponse& p);
	void to_json(json& j, const ProtocolMessage& p);
	void to_json(json& j, const Event& p);
	void to_json(json& j, const TerminatedEvent& p); 
	void to_json(json& j, const InitializedEvent& p);

	void to_json(json& j, const SetBreakpointsResponseBody& p);
	void to_json(json& j, const SetBreakpointsResponse& p);
	void to_json(json& j, const Breakpoint& p);

	void to_json(json& j, const StoppedEvent& p);	
	void to_json(json& j, const StoppedEventBody& p);

	void from_json(const json& j, ContinueRequest& p);
	void from_json(const json& j, ContinueArguments& p);
	void to_json(json& j, const ContinueResponse& p);
	void to_json(json& j, const ContinueResponseBody& p);

	void to_json(json& j, const ThreadsResponseBody& p);
	void to_json(json& j, const Thread& p);
	void to_json(json& j, const ThreadsResponse& p);
	void from_json(const json& j, ThreadsResponse& p);
	
	void to_json(json& j, const StackFrame& p);
	void to_json(json& j, const Source& p);	
	
	void to_json(json& j, const StackTraceResponse& p);
	void to_json(json& j, const StackTraceResponseBody& p);
	
	void from_json(const json& j, StackTraceRequest& p);
	void from_json(const json& j, ValueFormat& p);
	void from_json(const json& j, StackFrameFormat& p);
	void from_json(const json& j, StackTraceArguments& p);

	void to_json(json& j, const NextResponse& p);
	void from_json(const json& j, NextRequest& p);
	void from_json(const json& j, NextArguments& p);

	void to_json(json& j, const StepInResponse& p);
	void from_json(const json& j, StepInRequest& p);
	void from_json(const json& j, StepInArguments& p);

	void to_json(json& j, const ScopesResponse& p);
	void to_json(json& j, const ScopesResponseBody& p);
	void to_json(json& j, const ScopesArguments& p);
	void to_json(json& j, const Scope& p);
	void to_json(json& j, const ValueFormat& p);
	void to_json(json& j, const VariablesArguments& p);
	
}

    

#endif