## CS 305 Module Eight Journal
### Artemis Financial Security Project Reflection

### Client Summary
Artemis Financial is a financial services company that manages sensitive data, including investment accounts, retirement plans, and insurance records. The client needed a vulnerability assessment of their web application to identify security risks and improve protection of customer data. The main issue was weak security practices, including insecure communication, lack of input validation, and outdated dependencies, which increased exposure to attacks :contentReference[oaicite:0]{index=0}.

### What I Did Well
I identified key vulnerabilities across the application, including hardcoded credentials, missing authentication, insecure HTTP usage, and weak cryptographic practices. I combined manual review with automated dependency scanning, which provided broader coverage. Secure coding is important because it protects data integrity, prevents unauthorized access, and reduces risk to the organization.

### Challenging or Helpful Areas
Manual code review was the most challenging part, especially identifying how input handling and API exposure could be exploited. Static analysis was the most helpful, since it clearly identified known vulnerabilities and provided direct remediation guidance.

### Layers of Security
I recommended enforcing HTTPS with TLS, replacing weak hashing algorithms with SHA-256 or bcrypt, adding authentication and authorization, validating all inputs, updating dependencies, and implementing logging and monitoring. In the future, I would continue using OWASP Dependency-Check and OWASP Top Ten as a baseline for assessing vulnerabilities and selecting mitigation strategies.

### Ensuring Security and Functionality
I maintained functionality by focusing on targeted security fixes without changing core application behavior. After refactoring, I verified results by re-running dependency checks and reviewing the code for new issues. This ensures that security improvements do not introduce additional vulnerabilities.

### Tools and Practices
I used manual code review, OWASP Dependency-Check, and standard secure coding practices such as input validation, proper error handling, and strong encryption. These are repeatable and applicable to future projects.

### What I Would Show Employers
I would include the completed vulnerability assessment report and mitigation plan. This work demonstrates the ability to identify security risks, analyze code, and apply practical solutions in a structured way.

## CS 320
### Reflection

I ensure my code is functional and secure by combining careful design with thorough automated testing. In these projects, I focused on writing unit tests that validate both expected behavior and edge cases. Running tests continuously helps catch regressions early. I also enforce input validation, clear constraints, and defensive programming practices to reduce the risk of invalid data or unintended behavior.

I interpret user needs by starting with the stated requirements and translating them into concrete, testable behaviors. I break features into smaller rules that can be verified through unit tests. This helps confirm that the implementation actually matches what the user or stakeholder expects. When requirements are unclear, I focus on boundary conditions and realistic usage scenarios to guide design decisions.

My approach to designing software is incremental and test focused. I begin by identifying core responsibilities for each class and keeping components small and focused. I prefer simple, readable designs that are easy to test and maintain. Writing tests alongside development helps guide the structure of the code and ensures that quality is built into the process rather than added at the end.


## CS 255 Module Eight Journal
### DriverPass Project Summary
The DriverPass project involved designing a web-based system for a driver training company. The client needed a system that allowed students to schedule lessons and access training materials, while giving staff the ability to manage users, instructors, vehicles, and appointments in a centralized platform.

### What I Did Well
I successfully gathered and documented clear business requirements and carried them through into the system design. The UML diagrams and design artifacts closely matched the client’s needs and provided a logical, well-structured representation of the system.

### What I Would Revise
If revising this work, I would expand on nonfunctional requirements such as security, performance, and scalability. Adding more detail about how these concerns influence system architecture would strengthen the overall design.

### User Needs and Design
I interpreted user needs by examining different user roles and their workflows within the system. These needs were implemented using use cases and UML diagrams to ensure the system supported real-world interactions. Considering user needs is critical to creating a system that is both functional and user-friendly.

### My Design Approach
My approach to software design begins with understanding stakeholder goals and system requirements. I then use modeling techniques such as UML diagrams and iterative refinement to develop a clear and adaptable system design. In future projects, I plan to continue improving my designs through feedback and validation.


## CS 230 Software Design Document – The Gaming Room

### Client Summary
The client, The Gaming Room, wanted to expand their Android game *Draw It or Lose It* to multiple platforms. The software requirements included supporting multi-user gameplay, scaling across different operating systems, and maintaining strong performance, memory, and storage management.

### Strengths
I did particularly well in evaluating the pros and cons of each operating platform and clearly documenting how the client’s needs map to technical solutions. The table and recommendations provide a concise summary that could be useful to both technical and non-technical stakeholders.

### Helpful Process
Working through the design document helped me think about the software architecture before coding. Identifying memory and storage strategies, distributed systems considerations, and security needs gave me a better roadmap for how code should be structured later.

### Possible Revisions
If I could revise one part, I would expand the security section with more detail on specific threats and mitigations. This would improve the completeness of the recommendations and show a stronger focus on protecting user data.

### User Needs
I interpreted the user’s needs by focusing on cross-platform compatibility, scalability, and a smooth gameplay experience. Considering user needs is essential because software succeeds only if it solves real problems and provides a positive experience.

### Design Approach
My approach was to evaluate each platform carefully, consider trade-offs, and recommend a solution that balances cost, scalability, and security. In the future, I would continue to use structured design documents and include diagrams to visualize architecture, since this helps communicate ideas more effectively.
