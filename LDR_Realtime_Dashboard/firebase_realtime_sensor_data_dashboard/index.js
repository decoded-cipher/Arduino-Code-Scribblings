var light = [];
var firebase = new Firebase(".............................................");           // my-realtime-database.firebaseio.com/
firebase.on('value', function (snapshot) {

    for (let i in snapshot.val().light) {
        light.push(snapshot.val().light[i]);
    }


    light = light.slice(light.length - 20, light.length);
    light.forEach((o, i, a) => a[i] = o * 100 / 1024);
    drawGraph(light);
});

function drawGraph(light) {
    // var labels = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19];
    var labels = ['Before 19 min', 'Before 18 min', 'Before 17 min', 'Before 16 min', 'Before 15 min', 'Before 14 min', 'Before 13 min', 'Before 12 min', 'Before 11 min', 'Before 10 min', 'Before 09 min', 'Before 08 min', 'Before 07 min', 'Before 06 min', 'Before 05 min', 'Before 04 min', 'Before 03 min', 'Before 02 min', 'Before 01 min', 'At Present'];

    var ctx = document.getElementById("myChart").getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: "Percentage of Light [%]",
                labelString: "light",

                borderColor: 'rgb(145, 70, 65)',
                backgroundColor: 'rgb(145, 70, 65)',
                fill: false,
                data: light,
                yAxisID: "y-axis-temp",

            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            hoverMode: 'index',
            stacked: false,
            title: {
                display: true,
                text: 'Real-time LDR Value Measurements'
            },

            scales: {
                yAxes: [{
                    type: "linear",
                    display: true,
                    position: "left",
                    id: "y-axis-temp",
                    ticks: {
                        beginAtZero: true,
                        suggestedMax: 50
                    }

                }],
            }
        }
    });
}