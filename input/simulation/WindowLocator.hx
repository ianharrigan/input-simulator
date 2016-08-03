package input.simulation;

import cpp.ConstCharStar;
import cpp.RawPointer;

@:unreflective
@:include("WindowLocatorImpl.h")
@:native("WindowLocatorImpl*")
@:buildXml("<include name=\"${haxelib:input-simulator}/Build.xml\" />")
extern class WindowLocator {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // creation functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("new WindowLocatorImpl")      public static function create():WindowLocator;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // instance functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("FindByTitle")                public function findByTitle(title:ConstCharStar):Bool;
    @:native("FindByProcessId")            public function findByProcessId(processId:Int):Bool;
    @:native("BringToFront")               public function bringToFront():Void;
    @:native("HasWindow")                  public function hasWindow():Bool;
    @:native("GetWindow")                  public function getWindow():RawPointer<cpp.Void>;
    @:native("Close")                      public function close():Void;
}
