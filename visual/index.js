//import Chart from "chart.js";

const my_data = []
const clusters = []
let number_clusters

const createClusters = (cluster) => {
    clusters.push({
        x: cluster[0],
        y: cluster[1],
        label: cluster[2]
    })
}

const createPoint = point => {
    my_data.push({
        x: point[0],
        y: point[1],
        label: point[2]
    })
}

const getPointsColors = () => {
    const colors = []
    my_data.forEach(point => colors.push(point.label))
    return colors
}

const getClustersColors = () => {
    const colors = []
    clusters.forEach(cluster => colors.push(cluster.label))
    return colors
}


const initGraph = () => {
    const ctxBefore = document.getElementById('chartBefore')
    ctxBefore.style.display = "block"

    const chartBefore = new Chart(ctxBefore, {
        type: 'scatter',
        data: {
            labels: "",
            datasets: [
                {
                    label: "",
                    data: my_data,
                    pointBackgroundColor: "#000",
                }
            ],
        },
        options: {
            scales: {
                xAxes: [{
                    type: 'linear',
                    position: 'bottom'
                }]
            }
        }
    })
    chartBefore.update()


    const ctx = document.getElementById('chart')
    ctx.style.display = "block"

    const chartAfter = new Chart(ctx, {
        type: 'scatter',
        data: {
            labels: "",
            datasets: [
                {
                    label: "",
                    pointStyle: "triangle",
                    data: clusters,
                    pointBackgroundColor: getClustersColors(),
                    pointBorderColor: "#000",
                    pointRadius: 8,
                    pointHoverRadius: 8,
                },
                {
                    label: "",
                    data: my_data,
                    pointBackgroundColor: getPointsColors(),
                }
                
            ],
        },
        options: {
            scales: {
                xAxes: [{
                    type: 'linear',
                    position: 'bottom'
                }]
            }
        }
    })
    chartAfter.update()
}

const cleanData = () => {
    my_data.length = 0
    clusters.length = 0
}

const openFile = function(event) {
    const input = event.target

    const reader = new FileReader()
    reader.onload = function () {
        const text = reader.result.split("\n")
        number_clusters = parseInt(text[0])
        cleanData()
        for(let i = 1; i < number_clusters + 1; i++) {
            const cluster = text[i].split(" ")
            createClusters(cluster)
        }

        for(let i = number_clusters + 1; i < text.length-1; i++){
            const point = text[i].split(" ")
            createPoint(point)
        }

        initGraph()
    }  
    reader.readAsText(input.files[0])
}