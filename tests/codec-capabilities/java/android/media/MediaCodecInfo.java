package android.media;

// A host JVM fixture for the Java fallback; no Android decoder is allocated.
public final class MediaCodecInfo {
    public static final class VideoCapabilities {
        public boolean areSizeAndRateSupported(int width, int height, double rate) {
            Thread.yield();
            if (width < 0) throw new IllegalArgumentException("negative width");
            return width == 1920 && height == 1080 && rate == 30;
        }
    }
    public static final class CodecCapabilities {
        private final VideoCapabilities video = new VideoCapabilities();
        public VideoCapabilities getVideoCapabilities() {
            Thread.yield();
            return video;
        }
    }
    private final CodecCapabilities capabilities = new CodecCapabilities();
    public CodecCapabilities getCapabilitiesForType(String mime) {
        Thread.yield();
        return capabilities;
    }
}
