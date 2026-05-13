use axum::{
    extract::Multipart,
    response::IntoResponse,
    routing::{get, post},
    Router,
};

use std::{fs};

use tower_http::services::ServeDir; // allow serving files from disk over HTTP (the storage folder)

const STORAGE_DIR: &str = "storage"; // all uploaded files will be stored in './storage'

#[tokio::main]
async fn main() {

    fs::create_dir_all(STORAGE_DIR) // create the storage folder if it does not exist
        .expect("failed to create storage directory"); // if failuer

    // build our application with a single route
    let app = Router::new()
        .route("/", get(root)) // Call the async function root
        .route("/list", get(list_files))
        .route("/upload", get(upload_file))
        .nest_service("/download", ServeDir::new(STORAGE_DIR));

    // run our app with hyper, listening globally on port 3000
    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}

async fn root() -> &'static str {
    "Server is running"
}

async fn list_files() -> impl IntoResponse {
    let mut files = Vec::new();

    if let Ok(entries) = fs::read_dir(STORAGE_DIR) {
        for entry in entries.flatten() {
            if let Some(name) = entry.file_name().to_str() {
                files.push(name.to_string());
            }
        }
    }

    files.join("\n")
}

async fn upload_file(mut multipart: Multipart) -> impl IntoResponse {

}
