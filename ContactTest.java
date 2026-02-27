//ContactTest.java
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class ContactTest {

  @Test
  void createContact_validFields_succeeds() {
    Contact c = new Contact("12345", "Quinn", "Vana", "2175551234", "123 Main St");
    assertEquals("12345", c.getContactId());
    assertEquals("Quinn", c.getFirstName());
    assertEquals("Vana", c.getLastName());
    assertEquals("2175551234", c.getPhone());
    assertEquals("123 Main St", c.getAddress());
  }

  @Test
  void createContact_contactIdNull_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact(null, "A", "B", "1234567890", "Addr"));
  }

  @Test
  void createContact_contactIdTooLong_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("12345678901", "A", "B", "1234567890", "Addr"));
  }

  @Test
  void createContact_firstNameNull_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", null, "B", "1234567890", "Addr"));
  }

  @Test
  void createContact_firstNameTooLong_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "ABCDEFGHIJK", "B", "1234567890", "Addr"));
  }

  @Test
  void createContact_lastNameNull_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", null, "1234567890", "Addr"));
  }

  @Test
  void createContact_lastNameTooLong_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "ABCDEFGHIJK", "1234567890", "Addr"));
  }

  @Test
  void createContact_phoneNull_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", null, "Addr"));
  }

  @Test
  void createContact_phoneNot10Digits_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", "12345", "Addr"));
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", "123456789a", "Addr"));
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", "12345678901", "Addr"));
  }

  @Test
  void createContact_addressNull_throws() {
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", "1234567890", null));
  }

  @Test
  void createContact_addressTooLong_throws() {
    String longAddr = "1234567890123456789012345678901"; //31 chars
    assertThrows(IllegalArgumentException.class,
        () -> new Contact("1", "A", "B", "1234567890", longAddr));
  }

  @Test
  void setters_validUpdates_succeed() {
    Contact c = new Contact("1", "A", "B", "1234567890", "Addr");

    c.setFirstName("New");
    c.setLastName("Name");
    c.setPhone("0987654321");
    c.setAddress("456 Oak Ave");

    assertEquals("New", c.getFirstName());
    assertEquals("Name", c.getLastName());
    assertEquals("0987654321", c.getPhone());
    assertEquals("456 Oak Ave", c.getAddress());
  }

  @Test
  void setters_invalidUpdates_throw() {
    Contact c = new Contact("1", "A", "B", "1234567890", "Addr");

    assertThrows(IllegalArgumentException.class, () -> c.setFirstName(null));
    assertThrows(IllegalArgumentException.class, () -> c.setFirstName("ABCDEFGHIJK"));

    assertThrows(IllegalArgumentException.class, () -> c.setLastName(null));
    assertThrows(IllegalArgumentException.class, () -> c.setLastName("ABCDEFGHIJK"));

    assertThrows(IllegalArgumentException.class, () -> c.setPhone(null));
    assertThrows(IllegalArgumentException.class, () -> c.setPhone("123"));
    assertThrows(IllegalArgumentException.class, () -> c.setPhone("123456789a"));

    assertThrows(IllegalArgumentException.class, () -> c.setAddress(null));
    assertThrows(IllegalArgumentException.class, () -> c.setAddress("1234567890123456789012345678901"));
  }
}
