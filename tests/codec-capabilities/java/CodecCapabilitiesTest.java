import android.media.MediaCodecInfo;

public final class CodecCapabilitiesTest {
    static { System.loadLibrary("CodecCapabilitiesTest"); }
    private static native void probe(MediaCodecInfo codec, boolean warm);
    public static void main(String[] args) {
        probe(new MediaCodecInfo(), false); // concurrent first access
        probe(new MediaCodecInfo(), true);  // retain a pointer across re-probes
        System.out.println("shared codec capabilities: PASS");
    }
}
