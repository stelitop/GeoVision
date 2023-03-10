# GeoVision

A graphic tool for sketching geometrical problems, aimed for competitions.

This is a submission for the 2018-2019 NOIT (National Olympiad in IT), Bulgaria. 

For a documentation on how to use the tool refer to the Documentation word document (Bulgarian only), or read below for English.

# How to run

To start the program, download the repository and use double click the .exe file.

# How to use

In the middle of the window is the drawing pane and on the left are all the available tools. There are tools for:
- Move tool (Cursor) - Allows for moving around the plane by dragging and allows for moving individual points around (unless they are locked by definition)
- Point tool - Create a new point on the plane. The point can then be moved around freely with the move tool. If the point was created on top of a line or a circle, the point will stick to the element.
- Segment tool - Creates a new segment through two points.
- Line tool - Creates a new line that goes through two selected points.
- Circle with radius tool - Creates a circle, using one point as the center and another for the radius. The radius is the distance between the two points.
- Circle through 3 point tool - Creates a circle that passes through 3 points. Currently, if the 3 points are collinear it will crash the program.
- Altitude tool - Creates a segment from a point to a given line or segment that is perpendicular through it and passes through the point.
- Midpoint tool - Create the midpoint of a segment, or of two given points.
- Perpendicular line bisector tool - Creates a line that is perpendicular to a segment and goes through its midpoint. Also works if two points are selected instead of a segment.
- Angle bisector tool - Creates a line that bisects an angle in the middle. Select three points, of which the second will be the center of the angle.
- Outside angle bisector tool - Creates a line that bisects the outside angle of three points. It is essentially a line perpendicular to the regular angle bisector, going through the center point of the angle.
- Deletion tool - Deletes an element. Any elements whose definitions depend on that element are also deleted with it, e.g. points lying on lines, or elements depending on such points.

For convenience, any tool that relies on points can create the required points on the spot, instead of having to create points beforehand and select them. If a point is placed on the intersection of two 2d elements, it becomes locked in place and cannot be moved manually. If the elements are moved in such a way that the intersection no longer exists, the point will temporarily disappear.

While creating a new element, there is a dynamic preview of it that appears in blue. Once the element has been finalized it will apepear in orange.
