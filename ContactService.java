//ContactService.java
import java.util.HashMap;
import java.util.Map;

public class ContactService {
  private final Map<String, Contact> contacts = new HashMap<>();

  public void addContact(Contact contact) {
    if (contact == null) throw new IllegalArgumentException("contact must not be null");
    String id = contact.getContactId();
    if (contacts.containsKey(id)) throw new IllegalArgumentException("contactId already exists");
    contacts.put(id, contact);
  }

  public void addContact(String contactId, String firstName, String lastName, String phone, String address) {
    addContact(new Contact(contactId, firstName, lastName, phone, address));
  }

  public void deleteContact(String contactId) {
    validateId(contactId);
    if (!contacts.containsKey(contactId)) throw new IllegalArgumentException("contactId not found");
    contacts.remove(contactId);
  }

  public void updateFirstName(String contactId, String firstName) {
    getExisting(contactId).setFirstName(firstName);
  }

  public void updateLastName(String contactId, String lastName) {
    getExisting(contactId).setLastName(lastName);
  }

  public void updatePhone(String contactId, String phone) {
    getExisting(contactId).setPhone(phone);
  }

  public void updateAddress(String contactId, String address) {
    getExisting(contactId).setAddress(address);
  }

  //helper for tests and internal use
  public Contact getContact(String contactId) {
    validateId(contactId);
    return contacts.get(contactId);
  }

  private Contact getExisting(String contactId) {
    validateId(contactId);
    Contact c = contacts.get(contactId);
    if (c == null) throw new IllegalArgumentException("contactId not found");
    return c;
  }

  private static void validateId(String contactId) {
    if (contactId == null) throw new IllegalArgumentException("contactId must not be null");
    if (contactId.length() > 10) throw new IllegalArgumentException("contactId must be <= 10 characters");
    if (contactId.isBlank()) throw new IllegalArgumentException("contactId must not be blank");
  }
}
