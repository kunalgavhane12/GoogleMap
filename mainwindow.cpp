// #include "mainwindow.h"
// #include <QLabel>
// #include <QGridLayout>
// #include <QMessageBox>
// #include <QWebChannel>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent),
//     sourceLineEdit(new QLineEdit(this)),
//     destinationLineEdit(new QLineEdit(this)),
//     navigateButton(new QPushButton("Navigate", this)),
//     webView(new QWebEngineView(this)) {

//     // Set up central widget and main layout
//     QWidget *centralWidget = new QWidget(this);
//     QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//     // Create a layout for navigation inputs
//     QWidget *navigationWidget = new QWidget(this);
//     QVBoxLayout *navigationLayout = new QVBoxLayout(navigationWidget);

//     // Add widgets to navigation layout
//     QLabel *sourceLabel = new QLabel("Source (latitude,longitude):", this);
//     QLabel *destinationLabel = new QLabel("Destination (latitude,longitude):", this);
//     navigationLayout->addWidget(sourceLabel);
//     navigationLayout->addWidget(sourceLineEdit);
//     navigationLayout->addWidget(destinationLabel);
//     navigationLayout->addWidget(destinationLineEdit);
//     navigationLayout->addWidget(navigateButton);
//     navigationLayout->addStretch(); // Add stretch to push widgets to the top

//     // Add the navigation widget and map view to the main layout
//     mainLayout->addWidget(navigationWidget, 1); // 1/3 space for navigation
//     mainLayout->addWidget(webView, 2); // 2/3 space for the map

//     setCentralWidget(centralWidget);

//     // Define the Leaflet.js content
//     QString mapHtml = R"(
//         <!DOCTYPE html>
//         <html lang="en">
//         <head>
//             <meta charset="UTF-8">
//             <meta name="viewport" content="width=device-width, initial-scale=1.0">
//             <title>Leaflet Map</title>
//             <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
//             <style>
//                 #map {
//                     width: 100%;
//                     height: 100%;
//                     margin: 0;
//                 }
//                 body {
//                     margin: 0;
//                 }
//             </style>
//         </head>
//         <body>
//             <div id="map"></div>
//             <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
//             <script>
//                 const map = L.map('map').setView([17.3981, 78.4706], 13); // Default location and zoom
//                 L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
//                     attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a>'
//                 }).addTo(map);

//                 const markerGroup = L.layerGroup().addTo(map);

//                 function addRouteMarkers(source, destination) {
//                     markerGroup.clearLayers();

//                     const [srcLat, srcLng] = source.split(',').map(Number);
//                     L.marker([srcLat, srcLng]).addTo(markerGroup).bindPopup("Source").openPopup();

//                     const [destLat, destLng] = destination.split(',').map(Number);
//                     L.marker([destLat, destLng]).addTo(markerGroup).bindPopup("Destination").openPopup();

//                     map.fitBounds([
//                         [srcLat, srcLng],
//                         [destLat, destLng]
//                     ]);
//                 }

//                 // Expose the function globally
//                 window.addRouteMarkers = addRouteMarkers;
//             </script>
//         </body>
//         </html>
//     )";

//     // Load the map HTML content into the QWebEngineView
//     webView->setHtml(mapHtml);

//     // Connect button click to navigation slot
//     connect(navigateButton, &QPushButton::clicked, this, &MainWindow::onNavigate);
// }

// void MainWindow::onNavigate() {
//     // Get source and destination inputs
//     QString source = sourceLineEdit->text();
//     QString destination = destinationLineEdit->text();

//     // Validate inputs
//     if (source.isEmpty() || destination.isEmpty()) {
//         QMessageBox::warning(this, "Input Error", "Please enter both source and destination coordinates.");
//         return;
//     }

//     // Call JavaScript function to update markers
//     QString jsCommand = QString("addRouteMarkers('%1', '%2');").arg(source, destination);
//     webView->page()->runJavaScript(jsCommand);
// }


#include "mainwindow.h"
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    sourceLineEdit(new QLineEdit(this)),
    destinationLineEdit(new QLineEdit(this)),
    navigateButton(new QPushButton("Navigate", this)),
    webView(new QWebEngineView(this)) {

    // Set up central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Create a layout for navigation inputs
    QWidget *navigationWidget = new QWidget(this);
    QVBoxLayout *navigationLayout = new QVBoxLayout(navigationWidget);

    // Add widgets to navigation layout
    QLabel *sourceLabel = new QLabel("Source (location name):", this);
    QLabel *destinationLabel = new QLabel("Destination (location name):", this);
    navigationLayout->addWidget(sourceLabel);
    navigationLayout->addWidget(sourceLineEdit);
    navigationLayout->addWidget(destinationLabel);
    navigationLayout->addWidget(destinationLineEdit);
    navigationLayout->addWidget(navigateButton);
    navigationLayout->addStretch(); // Add stretch to push widgets to the top

    // Add the navigation widget and map view to the main layout
    mainLayout->addWidget(navigationWidget, 1); // 1/3 space for navigation
    mainLayout->addWidget(webView, 2); // 2/3 space for the map

    setCentralWidget(centralWidget);

    // Set initial map view
    QString initialMapUrl = "https://www.google.com/maps";
    webView->setUrl(QUrl(initialMapUrl));

    // QString MapUrl = "http://0.0.0.0:8081";
    // webView->setUrl(QUrl(MapUrl));

    // Connect button click to navigation slot
    connect(navigateButton, &QPushButton::clicked, this, &MainWindow::onNavigate);
}


void MainWindow::onNavigate() {
    // Get source and destination inputs
    QString source = sourceLineEdit->text();
    QString destination = destinationLineEdit->text();

    // Validate inputs
    if (source.isEmpty() || destination.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both source and destination.");
        return;
    }

    // Construct navigation URL for Google Maps
    QString navigationUrl = QString("https://www.google.com/maps/dir/%1/%2")
                                .arg(source, destination);

    // Load the navigation URL in the web view
    webView->setUrl(QUrl(navigationUrl));
}
