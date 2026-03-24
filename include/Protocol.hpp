#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include <string>
#include <vector>
#include <optional>
#include "json.hpp"
/**
 * https://github.com/Microsoft/vscode-debugadapter-node/tree/master/protocol
 *
 *
*/
//Protocol Version 1.71
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
		/** Ids of the breakpoints that triggered the event. */
		vector<int> hitBreakpointIds;//op
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
		/** Client supports memory references. */
		bool supportsMemoryReferences;
		/** Client supports progress reporting. */
		bool supportsProgressReporting;
		/** Client supports the invalidated event. */
		bool supportsInvalidatedEvent;
		/** Client supports the memory event. */
		bool supportsMemoryEvent;
		/** Client supports ANSI styling in OutputEvent messages. */
		bool supportsANSIStyling;
		/** Client supports args interpreted by the shell. */
		bool supportsArgsCanBeInterpretedByShell;
		/** Client supports the startDebugging request. */
		bool supportsStartDebuggingRequest;
		InitializeRequestArguments() : linesStartAt1(),columnsStartAt1(),supportsVariableType(),supportsVariablePaging(),
			supportsRunInTerminalRequest(),supportsMemoryReferences(),supportsProgressReporting(),
			supportsInvalidatedEvent(),supportsMemoryEvent(),supportsANSIStyling(),
			supportsArgsCanBeInterpretedByShell(),supportsStartDebuggingRequest()
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
		/** If true, continue only the specified thread. */
		std::optional<bool> singleThread;
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
		/** Stepping granularity. */
		string granularity;//?: 'statement' | 'line' | 'instruction'
		/** If true, execute only the specified thread. */
		std::optional<bool> singleThread;
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
		/** Stepping granularity. */
		string granularity;//?: 'statement' | 'line' | 'instruction'
		/** If true, execute only the specified thread. */
		std::optional<bool> singleThread;
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

/** An ExceptionFilterOptions is used to specify an exception filter together with a condition for the setExceptionBreakpoints request. */
	struct ExceptionFilterOptions {
		/** ID of an exception filter returned by the 'exceptionBreakpointFilters' capability. */
		string filterId;
		/** An optional expression for conditional exception breakpoints. */
		string condition;
	};

struct SetExceptionBreakpointsArguments{
	vector<string> filters;
	/** A list of exception filter options. */
	vector<ExceptionFilterOptions> filterOptions;
};
class SetExceptionBreakpointsRequest : public Request {
	
		// command: 'setExceptionBreakpoints';
		public:
			SetExceptionBreakpointsArguments arguments;
	};

class SetExceptionBreakpointsResponse: public Response {	
	public:	
	SetExceptionBreakpointsResponse(SetExceptionBreakpointsRequest &req) : Response((Request&) req)
	{}
};

/** An ExceptionBreakpointsFilter is shown in the UI as an option for configuring how exceptions are dealt with. */
	struct ExceptionBreakpointsFilter {
		/** The internal ID of the filter. This value is passed to the setExceptionBreakpoints request. */
		string filter;
		/** The name of the filter. This will be shown in the UI. */
		string label;
		/** Initial value of the filter. If not specified a value 'false' is assumed. */
		bool _default;
		/** Controls whether a condition can be specified for this filter option. */
		bool supportsCondition;
		/** A help text providing info about the condition. This string is shown as the placeholder text for a text box and must be translated. */
		string conditionDescription;
		ExceptionBreakpointsFilter():_default(false),supportsCondition(false){}
	};

    /** Information about the capabilities of a debug adapter. */
    struct Capabilities {
		Capabilities():supportsConfigurationDoneRequest(),supportsFunctionBreakpoints(),supportsConditionalBreakpoints(),supportsHitConditionalBreakpoints(),supportsEvaluateForHovers(),supportsStepBack(),supportsSetVariable(),
		supportsRestartFrame(),supportsGotoTargetsRequest(),supportsStepInTargetsRequest(),supportsCompletionsRequest(),supportsModulesRequest(),supportsRestartRequest(),supportsExceptionOptions(),
		supportsValueFormattingOptions(),supportsExceptionInfoRequest(),supportTerminateDebuggee(),supportsDelayedStackTraceLoading(),supportsLoadedSourcesRequest(),
		supportsLogPoints(),supportsTerminateRequest(),supportsDataBreakpoints(),supportsReadMemoryRequest(),supportsWriteMemoryRequest(),supportsDisassembleRequest(),
		supportsCancelRequest(),supportsBreakpointLocationsRequest(),supportsClipboardContext(),supportsSteppingGranularity(),supportsInstructionBreakpoints(),
		supportsExceptionFilterOptions(),supportsSingleThreadExecutionRequests(),supportsProgressReporting(),supportsInvalidatedEvent(),supportsMemoryReferences(),
		supportsMemoryEvent(),supportsStartDebuggingRequest(),supportsANSIStyling(),supportsDataBreakpointBytes()
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
		/** The debug adapter supports logpoints by interpreting 'logMessage' in SourceBreakpoints. */
		bool supportsLogPoints;
		/** The debug adapter supports the 'terminate' request. */
		bool supportsTerminateRequest;
		/** The debug adapter supports data breakpoints. */
		bool supportsDataBreakpoints;
		/** The debug adapter supports the 'readMemory' request. */
		bool supportsReadMemoryRequest;
		/** The debug adapter supports the 'writeMemory' request. */
		bool supportsWriteMemoryRequest;
		/** The debug adapter supports the 'disassemble' request. */
		bool supportsDisassembleRequest;
		/** The debug adapter supports the 'cancel' request. */
		bool supportsCancelRequest;
		/** The debug adapter supports the 'breakpointLocations' request. */
		bool supportsBreakpointLocationsRequest;
		/** The debug adapter supports the 'clipboard' context value in the 'evaluate' request. */
		bool supportsClipboardContext;
		/** The debug adapter supports stepping granularities for the stepping requests. */
		bool supportsSteppingGranularity;
		/** The debug adapter supports instruction breakpoints. */
		bool supportsInstructionBreakpoints;
		/** The debug adapter supports 'filterOptions' as an argument on the 'setExceptionBreakpoints' request. */
		bool supportsExceptionFilterOptions;
		/** The debug adapter supports single thread execution requests. */
		bool supportsSingleThreadExecutionRequests;
		/** The debug adapter supports progress reporting. */
		bool supportsProgressReporting;
		/** The debug adapter supports the invalidated event. */
		bool supportsInvalidatedEvent;
		/** The debug adapter supports memory references. */
		bool supportsMemoryReferences;
		/** The debug adapter supports the memory event. */
		bool supportsMemoryEvent;
		/** The debug adapter supports the 'startDebugging' request. */
		bool supportsStartDebuggingRequest;
		/** The debug adapter supports ANSI styling in OutputEvent messages. */
		bool supportsANSIStyling;
		/** The debug adapter supports data breakpoint bytes. */
		bool supportsDataBreakpointBytes;
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
		Source(string name,string path,int sr):name(name),path(path),sourceReference(sr){}
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
		/** A memory reference for the current instruction pointer in this frame. */
		string instructionPointerReference;//?: string;
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
		/** A memory reference to where the breakpoint is set. */
		string instructionReference;//?: string;
		/** An optional offset from the instruction reference. */
		int offset;//?: number;
		Breakpoint(){
			id = -1;
			line = -1;
			column = -1;
			endLine = -1;
			endColumn = -1;
			offset = -1;
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
		/** The mode of this breakpoint. If defined, this must be one of the 'breakpointModes' the debug adapter advertised in its Capabilities. */
		string mode;
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
		/** A memory reference associated with this variable. */
		string memoryReference;//?: string;
			Variable():variablesReference(0),namedVariables(0),indexedVariables(0){}
			Variable(string name, string value, int variablesReference):name(name),value(value),variablesReference(variablesReference),namedVariables(0),indexedVariables(0){}
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

	struct EvaluateResponseBody
	{

		/** The result of the evaluate request. */
		string result;//: string;
		/** The optional type of the evaluate result. */
		string type;//?: string;
		/** Properties of a evaluate result that can be used to determine how to render the result in the UI. */
		VariablePresentationHint presentationHint;//?: VariablePresentationHint;
		/** If variablesReference is > 0, the evaluate result is structured and its children can be retrieved by passing variablesReference to the VariablesRequest. */
		int variablesReference;//: number;
		/** The number of named child variables.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int namedVariables;//?: number;
		/** The number of indexed child variables.
			The client can use this optional information to present the variables in a paged UI and fetch them in chunks.
		*/
		int indexedVariables;//?: number;
		EvaluateResponseBody():variablesReference(-1),namedVariables(-1),indexedVariables(-1){}
	} ;



	

	/** Arguments for 'evaluate' request. */
	struct EvaluateArguments {
		/** The expression to evaluate. */
		string expression;//: string;
		/** Evaluate the expression in the scope of this stack frame. If not specified, the expression is evaluated in the global scope. */
		int frameId;//?: number;
		/** The context in which the evaluate request is run.
			Values:
			'watch': evaluate is run in a watch.
			'repl': evaluate is run from REPL console.
			'hover': evaluate is run from a data hover.
			etc.
		*/
		string context;//?: string;
		/** Specifies details on how to format the Evaluate result. */
		ValueFormat format;//?: ValueFormat;
	};
/** Evaluate request; value of command field is 'evaluate'.
		Evaluates the given expression in the context of the top most stack frame.
		The expression has access to any variables and arguments that are in scope.
	*/
	
	class EvaluateRequest : public Request {	
		// command: 'evaluate';
		public:
			EvaluateArguments arguments;
			
	};

	
	 /** Response to 'evaluate' request. */
	class EvaluateResponse : public Response {
		public:
			EvaluateResponseBody body;
			EvaluateResponse(EvaluateRequest &initreq) : Response((Request&) initreq)
			{}
	};

	struct SourceArguments {
	/**
	 * Specifies the source content to load. Either source.path or source.sourceReference must be specified.
	 */
	Source source;

	/**
	 * The reference to the source. This is the same as source.sourceReference. This is provided for backward compatibility since old backends do not understand the 'source' attribute.
	 */
	int sourceReference;
	};
	class SourceRequest : public Request {	
	//command: 'source';
		public:
		SourceArguments arguments;
	};

	struct SourceResponseBody
	{
		string content;
		string mimeType;

	};

	class SourceResponse : public Response {
		public:
			SourceResponseBody body;
			SourceResponse(SourceRequest &initreq) : Response((Request&) initreq)
			{}
	};

	struct OutputEventBody
	{
		string category;
		string output;
		/** Support for keeping an output log organized by grouping related messages. */
		string group;//?: 'start' | 'startCollapsed' | 'end'
		int variablesReference; //Number
		Source source;
		int line; //Number
		int column; //Number
		string data; //Any
		/** A reference that allows the client to request the location where the new value is declared. */
		int locationReference;//?: number

		OutputEventBody()
		{
			variablesReference = -1;
			line = -1;
			column = -1;
			locationReference = -1;
		}
	};

	class OutputEvent: public Event {
		public:
			OutputEventBody body;
			OutputEvent():Event("output"){				
			}
	};

	// -------------------------------------------------------------------------
	// New types for DAP v1.71
	// -------------------------------------------------------------------------

	/** A function breakpoint. */
	struct FunctionBreakpoint {
		string name;
		string condition;
		string hitCondition;
	};
	struct SetFunctionBreakpointsArguments {
		vector<FunctionBreakpoint> breakpoints;
	};
	class SetFunctionBreakpointsRequest : public Request {
	public:
		SetFunctionBreakpointsArguments arguments;
	};
	struct SetFunctionBreakpointsResponseBody {
		vector<Breakpoint> breakpoints;
	};
	class SetFunctionBreakpointsResponse : public Response {
	public:
		SetFunctionBreakpointsResponseBody body;
		SetFunctionBreakpointsResponse(SetFunctionBreakpointsRequest &req) : Response((Request&)req) {}
	};

	/** A data (memory) breakpoint. */
	struct DataBreakpoint {
		string dataId;
		string accessType;//?: 'read' | 'write' | 'readWrite'
		string condition;
		string hitCondition;
	};
	struct DataBreakpointInfoArguments {
		int variablesReference;//?: number — -1 if absent
		string name;
		int frameId;//?: number — -1 if absent
		DataBreakpointInfoArguments():variablesReference(-1),frameId(-1){}
	};
	struct DataBreakpointInfoResponseBody {
		string dataId;
		string description;
		vector<string> accessTypes;
		bool canPersist;
		DataBreakpointInfoResponseBody():canPersist(false){}
	};
	class DataBreakpointInfoRequest : public Request {
	public:
		DataBreakpointInfoArguments arguments;
	};
	class DataBreakpointInfoResponse : public Response {
	public:
		DataBreakpointInfoResponseBody body;
		DataBreakpointInfoResponse(DataBreakpointInfoRequest &req) : Response((Request&)req) {}
	};

	struct SetDataBreakpointsArguments {
		vector<DataBreakpoint> breakpoints;
	};
	class SetDataBreakpointsRequest : public Request {
	public:
		SetDataBreakpointsArguments arguments;
	};
	struct SetDataBreakpointsResponseBody {
		vector<Breakpoint> breakpoints;
	};
	class SetDataBreakpointsResponse : public Response {
	public:
		SetDataBreakpointsResponseBody body;
		SetDataBreakpointsResponse(SetDataBreakpointsRequest &req) : Response((Request&)req) {}
	};

	/** A location for a breakpoint (used in breakpointLocations response). */
	struct BreakpointLocation {
		int line;
		int column;//?: number — -1 if absent
		int endLine;//?: number — -1 if absent
		int endColumn;//?: number — -1 if absent
		BreakpointLocation():column(-1),endLine(-1),endColumn(-1){}
	};
	struct BreakpointLocationsArguments {
		Source source;
		int line;
		int column;//?: number — -1 if absent
		int endLine;//?: number — -1 if absent
		int endColumn;//?: number — -1 if absent
		BreakpointLocationsArguments():column(-1),endLine(-1),endColumn(-1){}
	};
	class BreakpointLocationsRequest : public Request {
	public:
		BreakpointLocationsArguments arguments;
	};
	struct BreakpointLocationsResponseBody {
		vector<BreakpointLocation> breakpoints;
	};
	class BreakpointLocationsResponse : public Response {
	public:
		BreakpointLocationsResponseBody body;
		BreakpointLocationsResponse(BreakpointLocationsRequest &req) : Response((Request&)req) {}
	};

	/** An instruction breakpoint. */
	struct InstructionBreakpoint {
		string instructionReference;
		int offset;//?: number — -1 if absent
		string condition;
		string hitCondition;
		string mode;
		InstructionBreakpoint():offset(-1){}
	};
	struct SetInstructionBreakpointsArguments {
		vector<InstructionBreakpoint> breakpoints;
	};
	class SetInstructionBreakpointsRequest : public Request {
	public:
		SetInstructionBreakpointsArguments arguments;
	};
	struct SetInstructionBreakpointsResponseBody {
		vector<Breakpoint> breakpoints;
	};
	class SetInstructionBreakpointsResponse : public Response {
	public:
		SetInstructionBreakpointsResponseBody body;
		SetInstructionBreakpointsResponse(SetInstructionBreakpointsRequest &req) : Response((Request&)req) {}
	};

	struct StepOutArguments {
		int threadId;
		string granularity;
		std::optional<bool> singleThread;
	};
	class StepOutRequest : public Request {
	public:
		StepOutArguments arguments;
	};
	class StepOutResponse : public Response {
	public:
		StepOutResponse(StepOutRequest &req) : Response((Request&)req) {}
	};

	struct StepBackArguments {
		int threadId;
		string granularity;
		std::optional<bool> singleThread;
	};
	class StepBackRequest : public Request {
	public:
		StepBackArguments arguments;
	};
	class StepBackResponse : public Response {
	public:
		StepBackResponse(StepBackRequest &req) : Response((Request&)req) {}
	};

	struct ReverseContinueArguments {
		int threadId;
		std::optional<bool> singleThread;
	};
	class ReverseContinueRequest : public Request {
	public:
		ReverseContinueArguments arguments;
	};
	class ReverseContinueResponse : public Response {
	public:
		ReverseContinueResponse(ReverseContinueRequest &req) : Response((Request&)req) {}
	};

	struct RestartFrameArguments {
		int frameId;
	};
	class RestartFrameRequest : public Request {
	public:
		RestartFrameArguments arguments;
	};
	class RestartFrameResponse : public Response {
	public:
		RestartFrameResponse(RestartFrameRequest &req) : Response((Request&)req) {}
	};

	struct PauseArguments {
		int threadId;
	};
	class PauseRequest : public Request {
	public:
		PauseArguments arguments;
	};
	class PauseResponse : public Response {
	public:
		PauseResponse(PauseRequest &req) : Response((Request&)req) {}
	};

	struct GotoTarget {
		int id;
		string label;
		int line;
		int column;//?: number — -1 if absent
		int endLine;//?: number — -1 if absent
		int endColumn;//?: number — -1 if absent
		string instructionPointerReference;
		GotoTarget():column(-1),endLine(-1),endColumn(-1){}
	};
	struct GotoArguments {
		int threadId;
		int targetId;
	};
	class GotoRequest : public Request {
	public:
		GotoArguments arguments;
	};
	class GotoResponse : public Response {
	public:
		GotoResponse(GotoRequest &req) : Response((Request&)req) {}
	};

	struct GotoTargetsArguments {
		Source source;
		int line;
		int column;//?: number — -1 if absent
		GotoTargetsArguments():column(-1){}
	};
	class GotoTargetsRequest : public Request {
	public:
		GotoTargetsArguments arguments;
	};
	struct GotoTargetsResponseBody {
		vector<GotoTarget> targets;
	};
	class GotoTargetsResponse : public Response {
	public:
		GotoTargetsResponseBody body;
		GotoTargetsResponse(GotoTargetsRequest &req) : Response((Request&)req) {}
	};

	struct SetVariableArguments {
		int variablesReference;
		string name;
		string value;
		ValueFormat format;
	};
	class SetVariableRequest : public Request {
	public:
		SetVariableArguments arguments;
	};

	struct ReadMemoryArguments {
		string memoryReference;
		int offset;//?: number — 0 if absent
		int count;
		ReadMemoryArguments():offset(0),count(0){}
	};
	class ReadMemoryRequest : public Request {
	public:
		ReadMemoryArguments arguments;
	};
	struct ReadMemoryResponseBody {
		string address;
		int unreadableBytes;//?: number — -1 if absent
		string data;//base64-encoded
		ReadMemoryResponseBody():unreadableBytes(-1){}
	};
	class ReadMemoryResponse : public Response {
	public:
		ReadMemoryResponseBody body;
		ReadMemoryResponse(ReadMemoryRequest &req) : Response((Request&)req) {}
	};

	struct WriteMemoryArguments {
		string memoryReference;
		int offset;//?: number — 0 if absent
		bool allowPartial;
		string data;//base64-encoded
		WriteMemoryArguments():offset(0),allowPartial(false){}
	};
	class WriteMemoryRequest : public Request {
	public:
		WriteMemoryArguments arguments;
	};
	struct WriteMemoryResponseBody {
		int offset;//?: number — -1 if absent
		int bytesWritten;//?: number — -1 if absent
		WriteMemoryResponseBody():offset(-1),bytesWritten(-1){}
	};
	class WriteMemoryResponse : public Response {
	public:
		WriteMemoryResponseBody body;
		WriteMemoryResponse(WriteMemoryRequest &req) : Response((Request&)req) {}
	};

	struct DisassembledInstruction {
		string address;
		string instructionBytes;
		string instruction;
		string symbol;
		Source location;
		int line;//?: number — -1 if absent
		int column;//?: number — -1 if absent
		int endLine;//?: number — -1 if absent
		int endColumn;//?: number — -1 if absent
		DisassembledInstruction():line(-1),column(-1),endLine(-1),endColumn(-1){}
	};
	struct DisassembleArguments {
		string memoryReference;
		int offset;
		int instructionOffset;
		int instructionCount;
		bool resolveSymbols;
		DisassembleArguments():offset(0),instructionOffset(0),instructionCount(0),resolveSymbols(false){}
	};
	class DisassembleRequest : public Request {
	public:
		DisassembleArguments arguments;
	};
	struct DisassembleResponseBody {
		vector<DisassembledInstruction> instructions;
	};
	class DisassembleResponse : public Response {
	public:
		DisassembleResponseBody body;
		DisassembleResponse(DisassembleRequest &req) : Response((Request&)req) {}
	};

	struct Module {
		string id;
		string name;
		string path;
		bool isOptimized;
		bool isUserCode;
		string version;
		string symbolStatus;
		string symbolFilePath;
		string dateTimeStamp;
		string addressRange;
		Module():isOptimized(false),isUserCode(false){}
	};
	struct ModulesArguments {
		int startModule;
		int moduleCount;
		ModulesArguments():startModule(0),moduleCount(0){}
	};
	class ModulesRequest : public Request {
	public:
		ModulesArguments arguments;
	};
	struct ModulesResponseBody {
		vector<Module> modules;
		int totalModules;
		ModulesResponseBody():totalModules(-1){}
	};
	class ModulesResponse : public Response {
	public:
		ModulesResponseBody body;
		ModulesResponse(ModulesRequest &req) : Response((Request&)req) {}
	};

	class LoadedSourcesRequest : public Request {};
	struct LoadedSourcesResponseBody {
		vector<Source> sources;
	};
	class LoadedSourcesResponse : public Response {
	public:
		LoadedSourcesResponseBody body;
		LoadedSourcesResponse(LoadedSourcesRequest &req) : Response((Request&)req) {}
	};

	struct CompletionItem {
		string label;
		string text;
		string sortText;
		string detail;
		string type;
		int start;
		int length;
		int selectionStart;
		int selectionLength;
		CompletionItem():start(-1),length(-1),selectionStart(-1),selectionLength(-1){}
	};
	struct CompletionsArguments {
		int frameId;
		string text;
		int column;
		int line;
		CompletionsArguments():frameId(-1),column(0),line(-1){}
	};
	class CompletionsRequest : public Request {
	public:
		CompletionsArguments arguments;
	};
	struct CompletionsResponseBody {
		vector<CompletionItem> targets;
	};
	class CompletionsResponse : public Response {
	public:
		CompletionsResponseBody body;
		CompletionsResponse(CompletionsRequest &req) : Response((Request&)req) {}
	};

	struct ExceptionDetails {
		string message;
		string typeName;
		string fullTypeName;
		string evaluateName;
		string stackTrace;
	};
	struct ExceptionInfoArguments {
		int threadId;
	};
	class ExceptionInfoRequest : public Request {
	public:
		ExceptionInfoArguments arguments;
	};
	struct ExceptionInfoResponseBody {
		string exceptionId;
		string description;
		string breakMode;//'never' | 'always' | 'unhandled' | 'userUnhandled'
		ExceptionDetails details;
	};
	class ExceptionInfoResponse : public Response {
	public:
		ExceptionInfoResponseBody body;
		ExceptionInfoResponse(ExceptionInfoRequest &req) : Response((Request&)req) {}
	};

	struct AttachRequestArguments {
		string restart;
	};
	class AttachRequest : public Request {
	public:
		AttachRequestArguments arguments;
	};
	class AttachResponse : public Response {
	public:
		AttachResponse(AttachRequest &req) : Response((Request&)req) {}
	};

	struct DisconnectArguments {
		std::optional<bool> restart;
		std::optional<bool> terminateDebuggee;
		std::optional<bool> suspendDebuggee;
	};
	class DisconnectRequest : public Request {
	public:
		DisconnectArguments arguments;
	};
	class DisconnectResponse : public Response {
	public:
		DisconnectResponse(DisconnectRequest &req) : Response((Request&)req) {}
	};

	struct TerminateArguments {
		std::optional<bool> restart;
	};
	class TerminateRequest : public Request {
	public:
		TerminateArguments arguments;
	};
	class TerminateResponse : public Response {
	public:
		TerminateResponse(TerminateRequest &req) : Response((Request&)req) {}
	};

	struct RestartArguments {};
	class RestartRequest : public Request {
	public:
		RestartArguments arguments;
	};
	class RestartResponse : public Response {
	public:
		RestartResponse(RestartRequest &req) : Response((Request&)req) {}
	};

	struct CancelArguments {
		int requestId;//?: number — -1 if absent
		string progressId;
		CancelArguments():requestId(-1){}
	};
	class CancelRequest : public Request {
	public:
		CancelArguments arguments;
	};
	class CancelResponse : public Response {
	public:
		CancelResponse(CancelRequest &req) : Response((Request&)req) {}
	};

	class ConfigurationDoneResponse : public Response {
	public:
		ConfigurationDoneResponse(ConfigurationDoneRequest &req) : Response((Request&)req) {}
	};
	class LaunchResponse : public Response {
	public:
		LaunchResponse(LaunchRequest &req) : Response((Request&)req) {}
	};

	/** Reverse request: adapter → client to run a command in a terminal. */
	struct RunInTerminalRequestArguments {
		string kind;//'integrated' | 'external'
		string title;
		string cwd;
		vector<string> args;
	};
	struct RunInTerminalResponseBody {
		int processId;//?: number — -1 if absent
		int shellProcessId;//?: number — -1 if absent
		RunInTerminalResponseBody():processId(-1),shellProcessId(-1){}
	};
	class RunInTerminalRequest : public Request {
	public:
		RunInTerminalRequestArguments arguments;
		RunInTerminalRequest() { type = "request"; command = "runInTerminal"; }
	};
	class RunInTerminalResponse : public Response {
	public:
		RunInTerminalResponseBody body;
		RunInTerminalResponse(RunInTerminalRequest &req) : Response((Request&)req) {}
	};

	/** Reverse request: adapter → client to start a new debug session. */
	struct StartDebuggingRequestArguments {
		string request;//'launch' | 'attach'
	};
	class StartDebuggingRequest : public Request {
	public:
		StartDebuggingRequestArguments arguments;
		StartDebuggingRequest() { type = "request"; command = "startDebugging"; }
	};
	class StartDebuggingResponse : public Response {
	public:
		StartDebuggingResponse(StartDebuggingRequest &req) : Response((Request&)req) {}
	};

	// New events -----------------------------------------------------------

	struct ProgressStartEventBody {
		string progressId;
		string title;
		int requestId;//?: number — -1 if absent
		bool cancellable;
		string message;
		double percentage;//?: 0-100 — -1 if absent
		ProgressStartEventBody():requestId(-1),cancellable(false),percentage(-1){}
	};
	class ProgressStartEvent : public Event {
	public:
		ProgressStartEventBody body;
		ProgressStartEvent() : Event("progressStart") {}
	};

	struct ProgressUpdateEventBody {
		string progressId;
		string message;
		double percentage;//?: 0-100 — -1 if absent
		ProgressUpdateEventBody():percentage(-1){}
	};
	class ProgressUpdateEvent : public Event {
	public:
		ProgressUpdateEventBody body;
		ProgressUpdateEvent() : Event("progressUpdate") {}
	};

	struct ProgressEndEventBody {
		string progressId;
		string message;
	};
	class ProgressEndEvent : public Event {
	public:
		ProgressEndEventBody body;
		ProgressEndEvent() : Event("progressEnd") {}
	};

	struct InvalidatedEventBody {
		/** Set of logical areas that got invalidated. */
		vector<string> areas;//?: ('all' | 'stacks' | 'threads' | 'variables')[]
		int threadId;//?: number — -1 if absent
		int stackFrameId;//?: number — -1 if absent
		InvalidatedEventBody():threadId(-1),stackFrameId(-1){}
	};
	class InvalidatedEvent : public Event {
	public:
		InvalidatedEventBody body;
		InvalidatedEvent() : Event("invalidated") {}
	};

	struct MemoryEventBody {
		string memoryReference;
		int offset;
		int count;
		MemoryEventBody():offset(0),count(0){}
	};
	class MemoryEvent : public Event {
	public:
		MemoryEventBody body;
		MemoryEvent() : Event("memory") {}
	};

	struct ContinuedEventBody {
		int threadId;
		bool allThreadsContinued;
		ContinuedEventBody():threadId(0),allThreadsContinued(false){}
	};
	class ContinuedEvent : public Event {
	public:
		ContinuedEventBody body;
		ContinuedEvent() : Event("continued") {}
	};

	struct ExitedEventBody {
		int exitCode;
		ExitedEventBody():exitCode(0){}
	};
	class ExitedEvent : public Event {
	public:
		ExitedEventBody body;
		ExitedEvent() : Event("exited") {}
	};

	struct ThreadEventBody {
		int threadId;
		string reason;//'started' | 'exited'
	};
	class ThreadEvent : public Event {
	public:
		ThreadEventBody body;
		ThreadEvent() : Event("thread") {}
	};

	struct ModuleEventBody {
		string reason;//'new' | 'changed' | 'removed'
		Module module;
	};
	class ModuleEvent : public Event {
	public:
		ModuleEventBody body;
		ModuleEvent() : Event("module") {}
	};

	struct LoadedSourceEventBody {
		string reason;//'new' | 'changed' | 'removed'
		Source source;
	};
	class LoadedSourceEvent : public Event {
	public:
		LoadedSourceEventBody body;
		LoadedSourceEvent() : Event("loadedSource") {}
	};

	struct ProcessEventBody {
		string name;
		int systemProcessId;//?: number — -1 if absent
		bool isLocalProcess;
		string startMethod;//?: 'launch' | 'attach' | 'attachForSuspendedLaunch'
		int pointerSize;//?: number — -1 if absent
		ProcessEventBody():systemProcessId(-1),isLocalProcess(true),pointerSize(-1){}
	};
	class ProcessEvent : public Event {
	public:
		ProcessEventBody body;
		ProcessEvent() : Event("process") {}
	};

	struct CapabilitiesEventBody {
		Capabilities capabilities;
	};
	class CapabilitiesEvent : public Event {
	public:
		CapabilitiesEventBody body;
		CapabilitiesEvent() : Event("capabilities") {}
	};

	// -------------------------------------------------------------------------
	// End of new types for DAP v1.71
	// -------------------------------------------------------------------------

	void from_json(const json& j, SourceArguments& p);
	void from_json(const json& j, SourceRequest& p);
	void to_json(json& j, const SourceResponse& p);
	void to_json(json& j, const SourceResponseBody& p);


	void to_json(json& j, const EvaluateResponse& p);
	void to_json(json& j, const EvaluateResponseBody& p);

	void from_json(const json& j, EvaluateArguments& p);
	void from_json(const json& j, EvaluateRequest& p);

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

	void to_json(json& j, const OutputEventBody& p);
	void to_json(json& j, const OutputEvent& p);

	// New serialization functions for DAP v1.71 --------------------------------

	// Capabilities (updated)
	void from_json(const json& j, InitializeRequestArguments& p);

	// SetFunctionBreakpoints
	void from_json(const json& j, FunctionBreakpoint& p);
	void from_json(const json& j, SetFunctionBreakpointsArguments& p);
	void from_json(const json& j, SetFunctionBreakpointsRequest& p);
	void to_json(json& j, const FunctionBreakpoint& p);
	void to_json(json& j, const SetFunctionBreakpointsResponseBody& p);
	void to_json(json& j, const SetFunctionBreakpointsResponse& p);

	// DataBreakpoints
	void from_json(const json& j, DataBreakpoint& p);
	void from_json(const json& j, DataBreakpointInfoArguments& p);
	void from_json(const json& j, DataBreakpointInfoRequest& p);
	void from_json(const json& j, SetDataBreakpointsArguments& p);
	void from_json(const json& j, SetDataBreakpointsRequest& p);
	void to_json(json& j, const DataBreakpointInfoResponseBody& p);
	void to_json(json& j, const DataBreakpointInfoResponse& p);
	void to_json(json& j, const SetDataBreakpointsResponseBody& p);
	void to_json(json& j, const SetDataBreakpointsResponse& p);

	// BreakpointLocations
	void from_json(const json& j, BreakpointLocationsArguments& p);
	void from_json(const json& j, BreakpointLocationsRequest& p);
	void to_json(json& j, const BreakpointLocation& p);
	void to_json(json& j, const BreakpointLocationsResponseBody& p);
	void to_json(json& j, const BreakpointLocationsResponse& p);

	// InstructionBreakpoints
	void from_json(const json& j, InstructionBreakpoint& p);
	void from_json(const json& j, SetInstructionBreakpointsArguments& p);
	void from_json(const json& j, SetInstructionBreakpointsRequest& p);
	void to_json(json& j, const SetInstructionBreakpointsResponseBody& p);
	void to_json(json& j, const SetInstructionBreakpointsResponse& p);

	// Execution control
	void from_json(const json& j, StepOutArguments& p);
	void from_json(const json& j, StepOutRequest& p);
	void to_json(json& j, const StepOutResponse& p);
	void from_json(const json& j, StepBackArguments& p);
	void from_json(const json& j, StepBackRequest& p);
	void to_json(json& j, const StepBackResponse& p);
	void from_json(const json& j, ReverseContinueArguments& p);
	void from_json(const json& j, ReverseContinueRequest& p);
	void to_json(json& j, const ReverseContinueResponse& p);
	void from_json(const json& j, RestartFrameArguments& p);
	void from_json(const json& j, RestartFrameRequest& p);
	void to_json(json& j, const RestartFrameResponse& p);
	void from_json(const json& j, PauseArguments& p);
	void from_json(const json& j, PauseRequest& p);
	void to_json(json& j, const PauseResponse& p);

	// Goto
	void from_json(const json& j, GotoArguments& p);
	void from_json(const json& j, GotoRequest& p);
	void to_json(json& j, const GotoResponse& p);
	void from_json(const json& j, GotoTargetsArguments& p);
	void from_json(const json& j, GotoTargetsRequest& p);
	void to_json(json& j, const GotoTarget& p);
	void to_json(json& j, const GotoTargetsResponseBody& p);
	void to_json(json& j, const GotoTargetsResponse& p);

	// SetVariable
	void from_json(const json& j, SetVariableArguments& p);
	void from_json(const json& j, SetVariableRequest& p);

	// Memory
	void from_json(const json& j, ReadMemoryArguments& p);
	void from_json(const json& j, ReadMemoryRequest& p);
	void to_json(json& j, const ReadMemoryResponseBody& p);
	void to_json(json& j, const ReadMemoryResponse& p);
	void from_json(const json& j, WriteMemoryArguments& p);
	void from_json(const json& j, WriteMemoryRequest& p);
	void to_json(json& j, const WriteMemoryResponseBody& p);
	void to_json(json& j, const WriteMemoryResponse& p);

	// Disassemble
	void from_json(const json& j, DisassembleArguments& p);
	void from_json(const json& j, DisassembleRequest& p);
	void to_json(json& j, const DisassembledInstruction& p);
	void to_json(json& j, const DisassembleResponseBody& p);
	void to_json(json& j, const DisassembleResponse& p);

	// Modules
	void from_json(const json& j, ModulesArguments& p);
	void from_json(const json& j, ModulesRequest& p);
	void to_json(json& j, const Module& p);
	void to_json(json& j, const ModulesResponseBody& p);
	void to_json(json& j, const ModulesResponse& p);

	// LoadedSources
	void from_json(const json& j, LoadedSourcesRequest& p);
	void to_json(json& j, const LoadedSourcesResponseBody& p);
	void to_json(json& j, const LoadedSourcesResponse& p);

	// Completions
	void from_json(const json& j, CompletionsArguments& p);
	void from_json(const json& j, CompletionsRequest& p);
	void to_json(json& j, const CompletionItem& p);
	void to_json(json& j, const CompletionsResponseBody& p);
	void to_json(json& j, const CompletionsResponse& p);

	// ExceptionInfo
	void from_json(const json& j, ExceptionInfoArguments& p);
	void from_json(const json& j, ExceptionInfoRequest& p);
	void to_json(json& j, const ExceptionDetails& p);
	void to_json(json& j, const ExceptionInfoResponseBody& p);
	void to_json(json& j, const ExceptionInfoResponse& p);

	// Attach / Disconnect / Terminate / Restart / Cancel
	void from_json(const json& j, AttachRequestArguments& p);
	void from_json(const json& j, AttachRequest& p);
	void to_json(json& j, const AttachResponse& p);
	void from_json(const json& j, DisconnectArguments& p);
	void from_json(const json& j, DisconnectRequest& p);
	void to_json(json& j, const DisconnectResponse& p);
	void from_json(const json& j, TerminateArguments& p);
	void from_json(const json& j, TerminateRequest& p);
	void to_json(json& j, const TerminateResponse& p);
	void from_json(const json& j, RestartArguments& p);
	void from_json(const json& j, RestartRequest& p);
	void to_json(json& j, const RestartResponse& p);
	void from_json(const json& j, CancelArguments& p);
	void from_json(const json& j, CancelRequest& p);
	void to_json(json& j, const CancelResponse& p);
	void to_json(json& j, const ConfigurationDoneResponse& p);
	void to_json(json& j, const LaunchResponse& p);

	// ExceptionFilterOptions
	void from_json(const json& j, ExceptionFilterOptions& p);

	// Reverse requests
	void to_json(json& j, const RunInTerminalRequestArguments& p);
	void to_json(json& j, const RunInTerminalRequest& p);
	void from_json(const json& j, RunInTerminalResponseBody& p);
	void from_json(const json& j, RunInTerminalResponse& p);
	void to_json(json& j, const StartDebuggingRequestArguments& p);
	void to_json(json& j, const StartDebuggingRequest& p);
	void from_json(const json& j, StartDebuggingResponse& p);

	// New events
	void to_json(json& j, const ProgressStartEventBody& p);
	void to_json(json& j, const ProgressStartEvent& p);
	void to_json(json& j, const ProgressUpdateEventBody& p);
	void to_json(json& j, const ProgressUpdateEvent& p);
	void to_json(json& j, const ProgressEndEventBody& p);
	void to_json(json& j, const ProgressEndEvent& p);
	void to_json(json& j, const InvalidatedEventBody& p);
	void to_json(json& j, const InvalidatedEvent& p);
	void to_json(json& j, const MemoryEventBody& p);
	void to_json(json& j, const MemoryEvent& p);
	void to_json(json& j, const ContinuedEventBody& p);
	void to_json(json& j, const ContinuedEvent& p);
	void to_json(json& j, const ExitedEventBody& p);
	void to_json(json& j, const ExitedEvent& p);
	void to_json(json& j, const ThreadEventBody& p);
	void to_json(json& j, const ThreadEvent& p);
	void to_json(json& j, const ModuleEventBody& p);
	void to_json(json& j, const ModuleEvent& p);
	void to_json(json& j, const LoadedSourceEventBody& p);
	void to_json(json& j, const LoadedSourceEvent& p);
	void to_json(json& j, const ProcessEventBody& p);
	void to_json(json& j, const ProcessEvent& p);
	void to_json(json& j, const CapabilitiesEventBody& p);
	void to_json(json& j, const CapabilitiesEvent& p);
}

    

#endif