package input.simulation;


import cpp.Char;
import cpp.ConstCharStar;
import cpp.RawPointer;

@:unreflective
@:include("KeyBoardImpl.h")
@:native("KeyBoardImpl*")
@:buildXml("<include name=\"../../Build.xml\" />")
extern class KeyBoard {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // creation functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("new KeyBoardImpl")      public static function create():KeyBoard;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // instance functions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    @:native("SetWindowHandle")     public function setWindowHandle(handle:RawPointer<cpp.Void>):Void;
    @:native("SetDelay")            public function setDelay(delay:Int):Void;
    
    @:native("Down")                public function down(string:Char):Void;
    @:native("Up")                  public function up(string:Char):Void;
    @:native("Press")               public function press(string:Char):Void;
    @:native("Type")                public function type(string:ConstCharStar):Void;
}
