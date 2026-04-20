---
layout: default
title: "Error Log"
description: "Errors made, doubts encountered. Documented as they happen."
---

<div class="log-grid">
{% assign sorted = site.logs | sort: "date" | reverse %}
{% for entry in sorted %}
<a class="log-card log-{{ entry.type }}" href="{{ entry.url | relative_url }}">
  <span class="log-meta">
    <span class="log-type">{{ entry.type }}</span>
    <span class="log-part">§{{ entry.part }}</span>
    <span class="log-date">{{ entry.date | date: "%b %d, %Y" }}</span>
  </span>
  <h3>{{ entry.title }}</h3>
  {% if entry.status == "open" %}<span class="log-status-open">unresolved</span>{% endif %}
  <div class="log-tags">
    {% for tag in entry.tags %}<span>{{ tag }}</span>{% endfor %}
  </div>
</a>
{% endfor %}
</div>

