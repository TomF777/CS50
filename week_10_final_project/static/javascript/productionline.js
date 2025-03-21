    const canvasProductionLine = document.getElementById("productionLine");

    // contex for 2d animation
    var ctx = canvasProductionLine.getContext("2d");

    // single stroke for product motion
    var productStep = 2;

    // x, y position of animated objects
    var positions = {
                     "product": {
                                  "xPos": 55,
                                  "yPos": 70
                                 },
                     "roboticGripper": {
                                         "xPos": 42,
                                         "yPos": 40
                                    },
                     "conveyor": {
                                   "x1Pos": 60,
                                   "y1Pos": 150,
                                   "x2Pos": 220,
                                   "y2Pos": 150
                                },
                     "chamber": {
                                  "xPos": 150,
                                  "yPos": 87
                                 },
    }

    // animation sequence step
    var seqStep = 0;

    // memory for last active sequence step
    var lastSeqStep;

    // production line running
    var productionStarted = true;

    var timeTick;

    var tickCount = 0;


    // image for "fire icon"
    const imgGripper = new Image();
    imgGripper.src = '/static/images/robotic-arm.png'


    function drawConveyor(x1Pos, y1Pos, x2Pos, y2Pos, running) {
        // draw conveyor with turning or stopped wheels
        // x1,y1 - left wheel position; x2,y2-right wheel position
        // running - machine status

        let positions;

        // depending if line running, display different wheels' stroke positions
        if (running && timeTick) {
                    positions = [[0, -8],[7, -5],[7, 5],[0, 8],[-7, 5],[-7, -5]];
                    lineDash = [2, 2];
        } else if (running && !timeTick) {
            positions = [[5, -7],[8, 0],[5, 7],[-5, 7],[-8, 0],[-5, -7]];
            lineDash = [3, 3];
        }

        else {
            positions = [[5, -7],[8, 0],[5, 7],[-5, 7],[-8, 0],[-5, -7]];
            lineDash = [];
        }

        // draw first wheel
        ctx.beginPath();
        ctx.setLineDash([]);
        ctx.strokeStyle = "rgb(0,0,255)";
        ctx.arc(x1Pos, y1Pos, 10, 0, Math.PI * 2);
        ctx.stroke();
        ctx.closePath();
        ctx.lineWidth = 1.2;
        ctx.strokeStyle = "rgb(0,0,0)";

        // draw inner spokes of wheel
        posLen = positions.length;
        for (let idx = 0; idx < posLen; idx++) {
            ctx.beginPath();
            ctx.setLineDash([]);
            ctx.strokeStyle = "rgb(0,0,255)";
            ctx.moveTo(x1Pos, y1Pos);
            ctx.lineTo(x1Pos + positions[idx][0], y1Pos + positions[idx][1]);
            ctx.stroke();
            ctx.closePath();
        }

        // draw second wheel
        ctx.beginPath();
        ctx.setLineDash([]);
        ctx.strokeStyle = "rgb(0,0,255)";
        ctx.arc(x2Pos, y2Pos, 10, 0, Math.PI * 2);
        ctx.stroke();
        ctx.closePath();

        // draw inner spokes of wheel
        posLen = positions.length;
        for (let idx = 0; idx < posLen; idx++) {
            ctx.beginPath();
            ctx.strokeStyle = "rgb(0,0,255)";
            ctx.setLineDash([]);
            ctx.moveTo(x2Pos, y2Pos);
            ctx.lineTo(x2Pos + positions[idx][0], y2Pos + positions[idx][1]);
            ctx.stroke();
            ctx.closePath();
        }

        // draw conveyor element connecting two wheels
        ctx.beginPath();
        ctx.setLineDash(lineDash);
        ctx.strokeStyle = "rgb(0,0,255)";
        ctx.lineWidth = 1.8;
        ctx.arc(x1Pos, y1Pos, 13, Math.PI / 2, 1.5 * Math.PI);
        ctx.arc(x2Pos, y2Pos, 13, 1.5 * Math.PI, Math.PI / 2);
        ctx.lineTo(x1Pos, y1Pos + 13);
        ctx.stroke();
        ctx.closePath();
    }


    function drawProduct(xPos, yPos) {
        // draw product on the conveyor
        ctx.beginPath();
        ctx.setLineDash([]);
        ctx.strokeStyle = "rgb(0,0,0)";
        ctx.fillStyle = "rgb(190,140,140)";
        ctx.fillRect(xPos, yPos, 20, 20);
        ctx.fill();
        ctx.stroke();
        ctx.closePath();
    }

    function drawChamber(xPos, yPos) {
        // draw industrial chamber
        ctx.lineWidth = 0.9;
        // big red shape
        ctx.beginPath();
        ctx.strokeStyle = "rgb(0,0,0)";
        ctx.fillStyle = "rgb(255,102,70)";
        ctx.roundRect(xPos, yPos, 40, 50, 2);
        ctx.fill();
        ctx.stroke();
        ctx.closePath();

        // inner blue shape
        ctx.beginPath();
        ctx.fillStyle = "rgb(160,226,235)";
        ctx.roundRect(xPos + 5, yPos + 10, 30, 23, 2);
        ctx.fill();
        ctx.stroke();
        ctx.closePath();

        // small measurement gauge
        ctx.beginPath();
        if (positions.product.xPos > 150 && positions.product.xPos < 180) {
            ctx.fillStyle = "rgb(255,255,0)";
        } else {
            ctx.fillStyle = "rgb(0,226,235)";
        }

        ctx.arc(xPos + 10, yPos + 42, 4, 0, 2 * Math.PI);
        ctx.fill();
        ctx.stroke();
        ctx.closePath();

        // small measurement gauge
        ctx.beginPath();
        if (positions.product.xPos > 150 && positions.product.xPos < 180) {
            ctx.fillStyle = "rgb(0,255,100)";
        } else {
            ctx.fillStyle = "rgb(0,226,235)";
        }

        ctx.arc(xPos + 30, yPos + 42, 4, 0, 2 * Math.PI);
        ctx.fill();
        ctx.stroke();
        ctx.closePath();

        // light indicator on the chamber's roof
        ctx.beginPath();
        ctx.lineWidth = 0;
        // change color when product inside chamber
        if (positions.product.xPos > 150 && positions.product.xPos < 180) {
            ctx.fillStyle = "rgb(255,0,0)";
        } else {
            ctx.fillStyle = "rgb(255,165,0)";
        }

        ctx.arc(xPos + 20, yPos - 10, 6, Math.PI, 2 * Math.PI);
        ctx.rect(xPos + 14, yPos - 10, 12, 9, 2);
        ctx.fill();
        ctx.closePath();
    }

    function drawRoboticGripper(xPos, Ypos) {
        ctx.drawImage(imgGripper, xPos, Ypos, 45, 45);
    }


    function drawScore() {
        ctx.font = "16px Arial";
        ctx.fillStyle = "rgb(45,45,120)";
        ctx.fillText("Score: " + score, 8, 20);
    }

    function drawGameLevel() {
        ctx.font = "16px Arial";
        ctx.fillStyle = "rgb(45,45,120)";
        ctx.fillText("Level: " + gameLevel, canvasProductionLine.width - 260, 20);
    }


    function draw() {
        ctx.clearRect(0, 0, canvasProductionLine.width, canvasProductionLine.height);
        ctx.fillStyle = "rgb(0,250,100)";
        ctx.fillRect(0, 0, canvasProductionLine.width, canvasProductionLine.height);

        ctx.font = "13px Lucida Console";
        ctx.fillStyle = "rgb(45,45,120)";
        ctx.fillText("Industrial Production", 64, 25);

        tickCount = tickCount + 1;

        // slower wheel rotation speed
        if ((tickCount % 2) == 0) {
            timeTick = !timeTick;
        }

        // detect stop when production line running
        if (productionRun == false && lastSeqStep > 0) {
            seqStep = 40;
        }

        // sequence for objects animation
        switch (seqStep) {
            case 0:
                lastSeqStep = 0;
                if (productionRun && lastSeqStep == 0) {
                    seqStep = 10;
                }
                break;

            // move robot gripper down
            case 10:
                lastSeqStep = 10;
                // positions for robot gripper
                if (positions.roboticGripper.yPos <= 85) {
                    positions.roboticGripper.yPos += 2;
                    positions.product.yPos += 2;

                    if (positions.roboticGripper.yPos >= 85) {
                        seqStep = 20;
                        }
                    }
                break;

            // move robot gripper up & transport product on the conveyor
            case 20:
                lastSeqStep = 20;
                if (positions.roboticGripper.yPos > 40) {
                    positions.roboticGripper.yPos -= 2;
                       if (positions.roboticGripper.yPos <= 40) {
                            positions.roboticGripper.yPos = 40;
                            }
                        }

                if (positions.roboticGripper.yPos < 75 && positions.product.xPos < 200) {
                    positions.product.xPos += productStep;
                } else if (positions.product.xPos >= 180) {
                            seqStep = 30;
                }

                break;

            // set product to the start position and restart sequence
            case 30:
                lastSeqStep = 30;
                positions.product.xPos = 55;
                positions.product.yPos = 70;
                seqStep = 0;
                break;

            // production stop
            case 40:
                if (productionRun) {
                    seqStep = lastSeqStep;
                }
                break;
            default:
                seqStep = 0;
        }


        drawRoboticGripper(positions.roboticGripper.xPos,
                           positions.roboticGripper.yPos,
                          );


        drawConveyor(positions.conveyor.x1Pos,
                     positions.conveyor.y1Pos,
                     positions.conveyor.x2Pos,
                     positions.conveyor.y2Pos,
                     productionRun
                    );

        drawProduct(positions.product.xPos,
                    positions.product.yPos);


        drawChamber(positions.chamber.xPos,
                    positions.chamber.yPos);

    }


    setInterval(draw, 50);
