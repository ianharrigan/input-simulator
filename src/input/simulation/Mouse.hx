package input.simulation;

import cpp.RawPointer;

@:unreflective
@:include("MouseImpl.h")
@:native("MouseImpl*")
@:buildXml("<include name=\"../../Build.xml\" />")
extern class Mouse {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // creation functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("new MouseImpl")      public static function create():Mouse;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // instance functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("SetWindowHandle")   public function setWindowHandle(handle:RawPointer<cpp.Void>):Void;
    @:native("SetDelay")          public function setDelay(delay:Int):Void;

    @:native("Up")                public function up(x:Int, y:Int):Void;
    @:native("Down")              public function down(x:Int, y:Int):Void;
    @:native("Move")              public function move(x:Int, y:Int):Void;
    @:native("Click")             public function click(x:Int, y:Int):Void;
    @:native("Stroke")            public function stroke(fromX:Int, fromY:Int, toX:Int, toY:Int):Void;
}
