
enum MyEnum {
	instance;

	MyEnum() {
		System.out.println("MyEnum constructor");
	}
}

public class TestEnum {
	public static void testEnum() {
		MyEnum myenum;
		MyEnum.instance.getClass();
	}

	public static void main(String args[]) {
		testEnum();
	}

}