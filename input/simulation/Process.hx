package input.simulation;

import cpp.ConstCharStar;
import cpp.RawPointer;

@:unreflective
@:include("ProcessImpl.h")
@:native("ProcessImpl*")
@:buildXml("<include name=\"${haxelib:input-simulator}/Build.xml\" />")
extern class Process {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // creation functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("new ProcessImpl")      public static function create():Process;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // instance functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("Open")                 public function open(file:ConstCharStar, wait:Int = 0):Bool;
    @:native("Kill")                 public function kill(processId:Int = 0):Bool;
    @:native("GetProcessId")         public function getProcessId():Int;
}