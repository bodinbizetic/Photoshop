package photoshop.selection;

public class Rectangle {

    private int width;
    private int height;
    private int x;
    private int y;

    public Rectangle(int width, int height, int x, int y) {
        this.width = width;
        this.height = height;
        this.x = x;
        this.y = y;
        toUpperLeftCorner();
    }

    private void toUpperLeftCorner() {
        if(width < 0){
            width = -width;
            x = x - width;
        }
        if(height < 0){
            height = -height;
            y = y - height;
        }
    }
}
