import QtQml 2.2
import QtQuick 2.0

// draws two arcs (portion of a circle)
// fills the circle with a lighter secondary color
// when pressed
Canvas {
    id: canvas
    width: 100
    height: 100
    antialiasing: true

    property color primaryColor: "white" // "orange"
    property color secondaryColor: "#1abc9c"
    property color textColor: "#1abc9c"

    property real centerWidth: width / 2
    property real centerHeight: height / 2
    property real radius: Math.min(canvas.width-10, canvas.height-11) / 2

    property real minimumValue: 0
    property real maximumValue: 100
    property real currentValue: 33
    property int lineWidth: 12

    // this is the angle that splits the circle in two arcs
    // first arc is drawn from 0 radians to angle radians
    // second arc is angle radians to 2*PI radians
    property real angle: (currentValue - minimumValue) / (maximumValue - minimumValue) * 2 * Math.PI

    // we want both circle to start / end at 12 o'clock
    // without this offset we would start / end at 9 o'clock
    property real angleOffset: -Math.PI / 2

    property string text: "Text"

    signal clicked()

    onPrimaryColorChanged: requestPaint()
    onSecondaryColorChanged: requestPaint()
    onMinimumValueChanged: requestPaint()
    onMaximumValueChanged: requestPaint()
    onCurrentValueChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d");
        ctx.save();

        ctx.clearRect(0, 0, canvas.width, canvas.height);

        // fills the mouse area when pressed
        // the fill color is a lighter version of the
        // secondary color

        if (mouseArea.pressed) {
            ctx.beginPath();
            ctx.lineWidColumnLayoutth = canvas.lineWidth;
            ctx.fillStyle = Qt.lighter(canvas.secondaryColor, 1.25);
            ctx.arc(canvas.centerWidth,
                    canvas.centerHeight,
                    canvas.radius,
                    0,
                    2*Math.PI);
            ctx.fill();
        }

        // First, thinner arc
        // From angle to 2*PI

        ctx.beginPath();
        ctx.lineWidth = canvas.lineWidth;
        ctx.strokeStyle = primaryColor;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                angleOffset + canvas.angle,
                angleOffset + 2*Math.PI);
        ctx.stroke();


        // Second, thicker arc
        // From 0 to angle

        ctx.beginPath();
        ctx.lineWidth = canvas.lineWidth;
        ctx.strokeStyle = canvas.secondaryColor;
        ctx.arc(canvas.centerWidth,
                canvas.centerHeight,
                canvas.radius,
                canvas.angleOffset,
                canvas.angleOffset + canvas.angle);
        ctx.stroke();

        ctx.restore();
    }

    Text {
        anchors.centerIn: parent
        text: qsTr(canvas.currentValue+"%")
        color: canvas.textColor
        font.pointSize: 14
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: canvas.clicked()
        onPressedChanged: canvas.requestPaint()
    }
}
