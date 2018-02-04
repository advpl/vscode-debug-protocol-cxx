import assert = require('assert');
import * as Path from 'path';
import {DebugClient} from 'vscode-debugadapter-testsupport';
import {DebugProtocol} from 'vscode-debugprotocol';
export function hello(){
    
    const DEBUG_ADAPTER = './out/mockDebug.js';
    
        const PROJECT_ROOT = Path.join(__dirname, '../../../');
        //const DATA_ROOT = Path.join(PROJECT_ROOT, 'src/tests/data/');
        /*const EXEC_PATH =  Path.join(PROJECT_ROOT, 'build/Debug/vscode-debug-protocol.exe');
        //const EXEC_PATH =  Path.join(PROJECT_ROOT, 'build/vscode-debug-protocol');
        const EXEC_DEBUG = "vscode-debug-protocol.exe";*/
        
        const EXEC_PATH =  Path.join(PROJECT_ROOT, 'build/Debug/AdvplDebugBridgeC.exe');
        const EXEC_DEBUG = "AdvplDebugBridgeC.exe";
        
        
    
        let dc: DebugClient;
        console.log(EXEC_DEBUG);
        dc = new DebugClient(EXEC_PATH,EXEC_DEBUG,"advpl");
        dc.start().then(info=>{
        console.log("iniciou");
        //dc.initializeRequest().then(info=>{
          //  console.log("voltou");
            let args : DebugProtocol.LaunchRequestArguments = {
                noDebug :true
            }
            dc.launch(args);
            }

        )
            
 //   });

}
hello();