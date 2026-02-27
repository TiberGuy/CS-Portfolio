//ContactServiceTest.java
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class ContactServiceTest {

  @Test
  void addContact_uniqueId_succeeds() {
    ContactService service = new ContactService();
    service.addContact("1", "Quinn", "Vana", "2175551234", "123 Main St");

    Contact c = service.getContact("1");
    assertNotNull(c);
    assertEquals("Quinn", c.getFirstName());
  }

  @Test
  void addContact_duplicateId_throws() {
    ContactService service = new ContactService();
    service.addContact("1", "A", "B", "1234567890", "Addr");

    assertThrows(IllegalArgumentException.class,
        () -> service.addContact("1", "C", "D", "0987654321", "Addr2"));
  }

  @Test
  void deleteContact_existingId_removes() {
    ContactService service = new ContactService();
    service.addContact("1", "A", "B", "1234567890", "Addr");

    service.deleteContact("1");
    assertNull(service.getContact("1"));
  }

  @Test
  void deleteContact_missingId_throws() {
    ContactService service = new ContactService();
    assertThrows(IllegalArgumentException.class, () -> service.deleteContact("nope"));
  }

  @Test
  void updateFields_existingId_updates() {
    ContactService service = new ContactService();
    service.addContact("1", "A", "B", "1234567890", "Addr");

    service.updateFirstName("1", "New");
    service.updateLastName("1", "Last");
    service.updatePhone("1", "0987654321");
    service.updateAddress("1", "456 Oak Ave");

    Contact c = service.getContact("1");
    assertEquals("New", c.getFirstName());
    assertEquals("Last", c.getLastName());
    assertEquals("0987654321", c.getPhone());
    assertEquals("456 Oak Ave", c.getAddress());
  }

  @Test
  void updateFields_missingId_throws() {
    ContactService service = new ContactService();
    assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("nope", "A"));
    assertThrows(IllegalArgumentException.class, () -> service.updateLastName("nope", "B"));
    assertThrows(IllegalArgumentException.class, () -> service.updatePhone("nope", "1234567890"));
    assertThrows(IllegalArgumentException.class, () -> service.updateAddress("nope", "Addr"));
  }

  @Test
  void updateFields_invalidValues_throw() {
    ContactService service = new ContactService();
    service.addContact("1", "A", "B", "1234567890", "Addr");

    assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("1", null));
    assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("1", "ABCDEFGHIJK"));

    assertThrows(IllegalArgumentException.class, () -> service.updatePhone("1", "123"));
    assertThrows(IllegalArgumentException.class, () -> service.updateAddress("1", "1234567890123456789012345678901"));
  }
}
