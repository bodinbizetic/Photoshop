package photoshop.selection;

public class Rectangle {

    private int width;
    private int height;
    private int x;
    private int y;

    public Rectangle(int x, int y, int width, int height) {
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

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
