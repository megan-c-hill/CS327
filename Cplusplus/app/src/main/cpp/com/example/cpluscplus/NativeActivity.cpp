#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue>

void android_main(struct android_app* state) {
struct engine engine;

	// Suppress link-time optimization that removes unreferenced code
	// to make sure glue isn't stripped.
	app_dummy();


	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(
    	engine.sensorManager,
        state->looper,
        LOOPER_ID_USER,
        NULL,
        NULL
    );
                        while (1) {
                                // Read all pending events.
                                int ident;
                                int events;
                                struct android_poll_source* source;


                                // If not animating, we will block forever waiting for events.
                                // If animating, we loop until all events are read, then continue
                                // to draw the next frame of animation.
                                while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL,
                                        &events,
                                        (void**)&source)) >= 0) {


                                    // Process this event.
                                    if (source != NULL) {
                                        source->process(state, source);
                                    }


                                    // If a sensor has data, process it now.
                                    if (ident == LOOPER_ID_USER) {
                                        if (engine.accelerometerSensor != NULL) {
                                            ASensorEvent event;
                                            while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                                                    &event, 1) > 0) {
                                                LOGI("accelerometer: x=%f y=%f z=%f",
                                                        event.acceleration.x, event.acceleration.y,
                                                        event.acceleration.z);
                                            }
                                        }
                                    }


                                // Check if we are exiting.
                                if (state->destroyRequested != 0) {
                                    engine_term_display(&engine);
                                    return;
                                }
                            }

                                if (engine.animating) {
                                    // Done with events; draw next animation frame.
                                    engine.state.angle += .01f;
                                    if (engine.state.angle > 1) {
                                        engine.state.angle = 0;
                                    }


                                    // Drawing is throttled to the screen update rate, so there
                                    // is no need to do timing here.
                                    engine_draw_frame(&engine);
                                }
}