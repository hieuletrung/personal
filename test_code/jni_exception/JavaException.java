// javac JavaException.java
// javah JavaException
// gcc JavaException.c -o libJavaException.so --shared -I /usr/lib/jvm/java-1.8.0-openjdk/include -I /usr/lib/jvm/java-1.8.0-openjdk/include/linux
// export LD_LIBRARY_PATH=.
// java JavaException

public class JavaException {

	public native void throwNativeException();

	public static void main(String args[]) {
		System.loadLibrary("JavaException");

		JavaException exception = new JavaException();
		try {
			exception.throwNativeException();
		} catch (Exception ex) {
			ex.printStackTrace();
		}

		try {
			exception.throwNativeException();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}