package input.simulation;

import cpp.Lib;
import cpp.Pointer;

class Main {
    public static function main() {
        var locator:WindowLocator = WindowLocator.create();
        var h = locator.findByTitle("Adobe Flash Player 11");
        locator.bringToFront();

        var mouse:Mouse = Mouse.create();
        mouse.setWindowHandle(h);

        mouse.stroke(200, 20, 200, 200);

        mouse.stroke(210, 200, 270, 20);
        mouse.stroke(270, 20, 330, 200);
        mouse.stroke(235, 120, 300, 120);

        mouse.stroke(340, 200, 340, 20);
        mouse.stroke(340, 20, 420, 200);
        mouse.stroke(420, 200, 420, 20);

        mouse.click(20, 20);

        var keyboard:KeyBoard = KeyBoard.create();
        keyboard.setWindowHandle(h);

        keyboard.type("first we found a candidate HWND\n");

        keyboard.type("now we can send chars to it\n\n");

        keyboard.type("this is a test line 1\n");
        keyboard.type("this is a test line 2\n");
        keyboard.type("this is a test line 3\n");
        keyboard.type("this is a test line 4\n");
        keyboard.type("this is a test line 5\n");

        keyboard.down(Keys.CONTROL_KEY);
        keyboard.down("a".charCodeAt(0));

        keyboard.up(Keys.CONTROL_KEY);
        keyboard.up("a".charCodeAt(0));

        keyboard.press(Keys.DELETE_KEY);
    }
}