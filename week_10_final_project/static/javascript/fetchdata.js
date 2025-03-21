// chart for sensor data and analytics results
const canvasChart1 = document.getElementById('dataChart1');

// chart for anomaly trend
const canvasChart2 = document.getElementById('dataChart2');

// status of animation production line
var productionRun;

canvasChart1.width = 200;
canvasChart1.height = 70;

canvasChart2.width = 200;
canvasChart2.height = 40;

// configuration for chart.js canvas
const chartLabels = [];
const dataChart1 = {
    labels: chartLabels,
    datasets: [{
            type: 'line',
            label: 'Sensor data',
            pointRadius: [2],
            backgroundColor: 'rgb(255, 195, 0)',
            borderColor: 'rgb(255,195, 0)',
            data: [],
        },
        {
            type: 'line',
            label: 'Mean',
            pointRadius: [2],
            backgroundColor: 'rgb(0, 255, 0)',
            borderColor: 'rgb(0, 255, 0)',
            data: [],
        },
        {
            type: 'line',
            label: 'Z-score',
            pointRadius: [2],
            backgroundColor: 'rgb(255, 237, 0)',
            borderColor: 'rgb(255, 237, 0)',
            data: [],
        },
        {
            type: 'line',
            type: 'line',
            label: '+Z-score threshold',
            pointRadius: [2],
            backgroundColor: 'rgb(0, 167, 255)',
            borderColor: 'rgb(0, 167, 255)',
            data: [],
        },
        {
            type: 'line',
            label: '-Z-score threshold',
            pointRadius: [2],
            backgroundColor: 'rgb(0, 167, 255)',
            borderColor: 'rgb(0, 167, 255)',
            data: [],
        },
        {
            type: 'bar',
            barThickness: 2,
            label: 'IsAnomaly',
            backgroundColor: 'rgb(255, 0, 0)',
            borderColor: 'rgb(255, 0, 0)',
            data: [],
        }
    ]
};

const dataChart2 = {
    labels: chartLabels,
    datasets: [{
        label: 'Anomaly trend [%]',
        pointRadius: [3],
        backgroundColor: 'rgb(255,0 , 0)',
        borderColor: 'rgb(255, 0, 0)',
        data: [],
    }, ]
};


const configChart1 = {
    //type: 'line',
    data: dataChart1,
    options: {
        scales: {
            x: {
                ticks: {
                    display: false
                }
            },
            y: {
                ticks: {
                    font: {
                        size: 16,
                    }
                },
                min: 80,
                max: 120
            }
        },

        plugins: {
            legend: {
                labels: {
                    font: {
                        size: 20,
                    }
                }
            }
        }
    }

};

const configChart2 = {
    type: 'line',
    data: dataChart2,
    options: {
        scales: {
                        x: {ticks: {display: false}},
                        y: { ticks :{
                                    font: {
                                            size: 16,
                                          }
                                    },
                            min: 0,
                            max: 100}
                      },

              plugins: {
                legend: {
                    labels: {
                        font: {
                            size: 20,
                              }
                            }
                        }
                      }
            }

};

const chart1 = new Chart(canvasChart1, configChart1);
const chart2 = new Chart(canvasChart2, configChart2);


async function requestData() {
  // send GET request and receive data from server

  // cyclically request data from server when production line running
  if (productionRun) {
      let requests = await fetch('/get_data');
      let data = await requests.json();

      dataModelCompleteness = parseInt(data[data.length - 1]["model_completeness"]);

      // progress bar for data model completeness
      if (dataModelCompleteness < 100) {
        document.getElementById('dataInnerProgress').innerHTML = "Building algorithm data model: " + dataModelCompleteness + "%";
      } else {
          document.getElementById('dataInnerProgress').innerHTML = "Algorithm model completed";
      }

      document.getElementById('dataCompleteStatus').style.width = dataModelCompleteness + "%";

      chart1.data.labels = data.map(item => item.timestamp);
      chart1.data.datasets[0].data = data.map(item => item.sensor_value);
      chart1.data.datasets[1].data = data.map(item => item.avg);
      chart1.data.datasets[2].data = data.map(item => item.avg + item.z_score);
      chart1.data.datasets[3].data = data.map(item => item.avg + Math.abs(item.z_score_thresh));
      chart1.data.datasets[4].data = data.map(item => item.avg - Math.abs(item.z_score_thresh));
      chart1.data.datasets[5].data = data.map(item => (item.anomaly * 92 ) );

      chart2.data.labels = data.map(item => item.timestamp);
      chart2.data.datasets[0].data = data.map(item => item.anomaly_ratio * 100);

      chart1.update();
      chart2.update();
  }
}


async function getControlStatus() {
    // send GET request and get control data from server

    let requests = await fetch('/get_control');
    let data = await requests.json();

    console.log(data["z_score_thresh"])
    console.log(data["sim_anomaly_level"])
    console.log(data["run"])
    console.log(data["time_window"])

    document.querySelector('#zScoreVal').value = data["z_score_thresh"];
    document.querySelector('#zScoreThreshold').value = data["z_score_thresh"];

    document.querySelector('#anomalySimLevel').value = data["sim_anomaly_level"];
    document.querySelector('#anomalySimLevelVal').value = data["sim_anomaly_level"];
    productionRun = data["run"];
}


async function sendControl(jsonKey, value) {
    // send POST request with control data to the server

    let requests = await fetch('/send_control', {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            [jsonKey]: value
        })
    });
    let response = await requests.text();
    console.log("post sent " + requests.ok + " " + requests.status + " " + response)
}


// 2 sec. refresh of data request
setInterval(requestData, 2000);


// slider handler
let zScore = document.querySelector('#zScoreThreshold');
zScore.addEventListener('change', function() {
    document.querySelector('#zScoreVal').value = this.value;
    sendControl(jsonKey = "zScoreThresh", this.value);
});

// slider handler
let simLevel = document.querySelector('#anomalySimLevel');
simLevel.addEventListener('change', function() {
    document.querySelector('#anomalySimLevelVal').value = this.value;
    sendControl(jsonKey = "anomalySimLevel", this.value);
});

// button Start/Stop handler
let startStop = document.querySelector('#btnStartStop');
startStop.addEventListener('click', function() {
    document.querySelector('#btnStartStop').value = this.value;
    productionRun = !productionRun;
    sendControl(jsonKey = "startStop", this.value);
});

// button Reset handler
let reset = document.querySelector('#btnReset');
reset.addEventListener('click', function() {
    document.getElementById('dataCompleteStatus').style.width = 0 + "%";
    document.getElementById('dataInnerProgress').innerHTML = "";
    document.querySelector('#btnReset').value = this.value;
    sendControl(jsonKey = "reset", this.value);
});

// select handler to determine time window of chart x-axis
let selector = document.querySelector(".form-select");

selector.addEventListener("change", (event) => {

    let timeWindow = parseInt(event.target.value)
    console.log("time window : " + timeWindow);
    sendControl(jsonKey = "timeWindow", timeWindow);
});
