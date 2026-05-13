use axum::{
    routing::{get, post},
    Router,
};

use std::{fs};

use tower_http::services::ServeDir; // allow serving files from disk over HTTP (the storage folder)

#[tokio::main]
async fn main() {

    const STORAGE_DIR: &str = "storage"; // all uploaded files will be stored in './storage'

    fs::create_dir_all(STORAGE_DIR) // create the storage folder if it does not exist
        .expect("failed to create storage directory"); // if failuer

    // build our application with a single route
    let app = Router::new()
        .route("/", get(root)); // Call the async function root

    // run our app with hyper, listening globally on port 3000
    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}

async fn root() -> &'static str {
    "Server is running"
}
