#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*void main() {
	string path = "test.png";
		Mat img = imread(path);
	imshow("Freame", img);
	waitKey(0);

}*/

/*void main() {
	VideoCapture video(0);
	Mat img;
	while (true) {
		video.read(img);
		imshow("Freame", img);
		waitKey(1);
	}
}*/

int main() {
    VideoCapture video(0); 
    if (!video.isOpened()) {
        cerr << "Error: gagal mempilkan camera" << endl;
        return -1;
    }
    CascadeClassifier facedetect;

    Mat img;
    facedetect.load("haarcascade_frontalface_default.xml");
    if (!facedetect.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error: Gagal memuat klasifikasi wajah cascade." << endl;
        return -1;
    }

    while (true) {
        video.read(img);

        vector<Rect> faces;
        
        facedetect.detectMultiScale(img, faces, 1.3, 5);
        
        cout << faces.size() << endl;

        for (int i = 0; i < faces.size(); i++) {
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50,50,255), 3);
            putText(img, to_string(faces.size()), Point(10.40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
        }

        imshow("Frame", img);
        // Break "q" untuk Stop
       if (waitKey(1) == 'q') {
            break;
       }
    }

    // Release the video capture object
    video.release();

    // Close the display window
    destroyAllWindows();

    return 0;
}
