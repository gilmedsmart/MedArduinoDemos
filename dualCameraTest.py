import cv2
import numpy as np

FHeight = 720
FWidthCr = 810
FWidthFl = 1280

# Function to process a frame: crop, rotate, and resize
def process_frame(frame, dbflag1=False):

    # Crop the frame    
    cropped_frame = frame[0:FHeight, (235):(235+FWidthCr)]
        
    # Rotate the frame by 90 degrees clockwise
    rotated_frame = cv2.rotate(cropped_frame, cv2.ROTATE_90_CLOCKWISE)

    # Resize the frame to fit the canvas
    resized_frame = rotated_frame #cv2.resize(rotated_frame, (FHeight,FWidthCr))

    if dbflag1:
        print("Orig " + str(frame.shape))
        print("Cropped " + str(cropped_frame.shape))
        print("Rot" + str(rotated_frame.shape))
        print("Resize " + str(resized_frame.shape))
    
    return resized_frame

# Initialize video capture from both cameras
cap1 = cv2.VideoCapture(0)  # Replace 0 with the actual index of the first camera
cap2 = cv2.VideoCapture(2)  # Replace 1 with the actual index of the second camera

cap1.set(cv2.CAP_PROP_FRAME_WIDTH, FWidthFl)
cap1.set(cv2.CAP_PROP_FRAME_HEIGHT, FHeight)
cap2.set(cv2.CAP_PROP_FRAME_WIDTH, FWidthFl)
cap2.set(cv2.CAP_PROP_FRAME_HEIGHT, FHeight)
# Check if cameras are opened successfully
if not cap1.isOpened() or not cap2.isOpened():
    print("Error: Could not open video capture devices.")
    exit()

dbflag = True

while True:
    # Read frames from both cameras
    ret1, frame1 = cap1.read()
    ret2, frame2 = cap2.read()

    if not ret1 or not ret2:
        break

    # Process the frames
    processed_frame1 = process_frame(frame1,dbflag)
    processed_frame2 = process_frame(frame2,dbflag)

    if (dbflag):
        print("Pre1 " + str(frame1.shape))
        print("Pre2 " + str(frame2.shape))
        print("Post1 " + str(processed_frame1.shape))
        print("Post2 " + str(processed_frame2.shape))
        dbflag = False

    # Create a single canvas to display both images side-by-side
    canvas = np.zeros((810, 1440, 3), dtype=np.uint8)
    canvas[:, :720,:] = processed_frame1
    canvas[:, 720:,:] = processed_frame2

    # Display the canvas
    cv2.imshow('Combined Video', canvas)

    # Exit if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture objects and close windows
cap1.release()
cap2.release()
cv2.destroyAllWindows()